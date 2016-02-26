#include "My3dsLoader.h"
#include "limits.h"

namespace DataStruct
{
	My3dsLoader::My3dsLoader()
	{
		file = NULL;
	}

	My3dsLoader::~My3dsLoader()
	{
		if(!file)
			lib3ds_file_free(file);
	}

	bool My3dsLoader::load3ds(const char* fname)
	{
		file =  lib3ds_file_open(fname);
		
		if(!file)
		{
			std::cerr << fname << " not found!\n";
			return false;
		}
		materialArray.resize(file->nmaterials);
		for(int i=0;i<file->nmaterials;i++)
			materialArray[i] = *(file->materials[i]);
		
		vCount = 0;
		extract_nodes(file->nodes);
		//std::cout << file->master_scale << std::endl;
		lib3ds_file_bounding_box_of_nodes (file, 1, 0, 0, bbMin, bbMax, 0);
		for(int t=0;t<3;t++)
		{
			bbMax[t]*=file->master_scale;
			bbMin[t]*=file->master_scale;
		}
		return true;
	}

	void My3dsLoader::saveTransformed3ds(const char* fname, const MyVector3D translate, const float alpha)
	{
		double sinz = sin(alpha);
		double cosz = cos(alpha);
		MyVector3D stranslate = translate/file->master_scale;

		for (Lib3dsNode *p =file->nodes->childs; p; p = p->next)
		{
			Lib3dsMeshInstanceNode *node = (Lib3dsMeshInstanceNode*)p;

			Lib3dsMesh* mesh = lib3ds_file_mesh_for_node(file, (Lib3dsNode *)node);
			if(!mesh || !mesh->nvertices) continue;

			{
				float inv_matrix[4][4], M[4][4];

				lib3ds_matrix_copy(M, node->base.matrix);
				lib3ds_matrix_translate(M, -node->pivot[0], -node->pivot[1], -node->pivot[2]);
				lib3ds_matrix_copy(inv_matrix, mesh->matrix);
				lib3ds_matrix_inv(inv_matrix);
				lib3ds_matrix_mult(M, M, inv_matrix);

				for (int i = 0; i < mesh->nvertices; ++i)
				{
					float tmp[3];
					lib3ds_vector_transform(tmp, M, mesh->vertices[i]);

					tmp[0] += stranslate[0];
					tmp[1] += stranslate[1];
					tmp[2] += stranslate[2];

					lib3ds_vector_copy(mesh->vertices[i], tmp);
					tmp[0] = mesh->vertices[i][0]*cosz  - mesh->vertices[i][1]*sinz;
					tmp[1] =  mesh->vertices[i][0]*sinz + mesh->vertices[i][1]*cosz;

					lib3ds_vector_copy(mesh->vertices[i], tmp);
				}

				node->pivot[0] = node->pivot[1] = node->pivot[2] = 0;
				memset(node->base.matrix,0,sizeof(node->base.matrix));
				memset(mesh->matrix,0,sizeof(mesh->matrix));
				node->base.matrix[0][0] = node->base.matrix[1][1] = node->base.matrix[2][2] = node->base.matrix[3][3] = 1;
				mesh->matrix[0][0] = mesh->matrix[1][1] = mesh->matrix[2][2] = mesh->matrix[3][3] = 1;
			}
		}

		if (!lib3ds_file_save(file, fname)) 
		{
			std::cerr << "ERROR: Saving 3ds file failed!\n";
			exit(-1);
		}
	}

	void My3dsLoader::extract_mesh(Lib3dsMeshInstanceNode *node)
	{
		Lib3dsMesh* mesh = lib3ds_file_mesh_for_node(file, (Lib3dsNode *)node);
		if(!mesh || !mesh->nvertices) return;

		float (*orig_vertices)[3];
		orig_vertices = (float(*)[3])malloc(sizeof(float) * 3 * mesh->nvertices);
		memcpy(orig_vertices, mesh->vertices, sizeof(float) * 3 * mesh->nvertices);
		{
			float inv_matrix[4][4], M[4][4];

			lib3ds_matrix_copy(M, node->base.matrix);
			lib3ds_matrix_translate(M, -node->pivot[0], -node->pivot[1], -node->pivot[2]);
			lib3ds_matrix_copy(inv_matrix, mesh->matrix);
			lib3ds_matrix_inv(inv_matrix);
			lib3ds_matrix_mult(M, M, inv_matrix);

			for (int i = 0; i < mesh->nvertices; ++i) {
				float tmp[3];
				lib3ds_vector_transform(tmp, M, mesh->vertices[i]);
				lib3ds_vector_copy(mesh->vertices[i], tmp);
			}
		}
		
		for(int i=0;i<mesh->nvertices;i++)
		{
			MyVector3D point(mesh->vertices[i]);
			point = point * file->master_scale;
			vectexArray.push_back(point);
		}

		for(int i=0;i<mesh->nfaces;i++)
		{
			Lib3dsFace  *face = &(mesh->faces[i]);
			faceArray.push_back(face->index[0]+vCount);
			faceArray.push_back(face->index[1]+vCount);
			faceArray.push_back(face->index[2]+vCount);

			faceIDArray.push_back(node->base.node_id);
			faceMaterialArray.push_back(face->material);
		}
		vCount+= mesh->nvertices;

		memcpy(mesh->vertices, orig_vertices, sizeof(float) * 3 * mesh->nvertices);
		free(orig_vertices);
	}

	void My3dsLoader::extract_nodes(Lib3dsNode *first_node)
	{
		for (Lib3dsNode *p = first_node; p; p = p->next) {
			if (p->type == LIB3DS_NODE_MESH_INSTANCE) {
				extract_mesh((Lib3dsMeshInstanceNode*)p);
				extract_nodes(p->childs);
			}
		}
	}

	const std::vector<Lib3dsMaterial> My3dsLoader::getMaterialArray()
	{
		return materialArray;
	}

	const std::vector<MyVector3D> My3dsLoader::getVertexArray()
	{
		return vectexArray;
	}

	const std::vector<int> My3dsLoader::getFaceArray()
	{
		return faceArray;
	}

	const std::vector<int> My3dsLoader::getFaceIDArray()
	{
		return faceIDArray;
	}

	const std::vector<int> My3dsLoader::getFaceMaterialArray()
	{
		return faceMaterialArray;
	}

	const char* My3dsLoader::getRootName()
	{
		if(file->nodes->type == LIB3DS_NODE_MESH_INSTANCE)
			return ((Lib3dsMeshInstanceNode*)(file->nodes))->instance_name;
		else
			return NULL;
	}

	const MyVector3D My3dsLoader::getBbMin()
	{
		return MyVector3D(bbMin);
	}

	const MyVector3D My3dsLoader::getBbMax()
	{
		return MyVector3D(bbMax);
	}

	const MyVector3D My3dsLoader::getCenter()
	{
		return (MyVector3D(bbMax)+MyVector3D(bbMin))/2;
	}

	void My3dsLoader::extractObjects(const char* fname, const char* outputDirectory)
	{
		std::ifstream in(fname);
		if(!in)
		{
			std::cerr << "Can't find  " << fname << "!\n";
			exit(-1);
		}
		objects.clear();
		int nObjects;
		in >> nObjects;

		std::string label;
		int count;

		for(int i=0; i<nObjects; i++)
		{
			in >>  label >> count;
			//int pos = label.find('(');

			MyObject o;
			//o.label = label.substr(0,pos);
			o.label = label;

			for(int i=0;i<count;i++)
			{
				int mID;
				in >> mID;
				o.meshIDs.insert(mID);
			}
			objects.push_back(o);
		}
		in.close();

		int id=0;
		for(int i=0;i<objects.size();i++)
		{
			if(!objects[i].label.compare("wall(ǽ)")) continue;
			
			char buf[500];
			sprintf(buf,"%s/%d.3ds",outputDirectory,id);
			saveObject(i,buf);
			id++;
		}
	}

	void My3dsLoader::flatObjects(const char* output)
	{
		objects.clear();
		MyObject o;
		o.label = "flat";

		for(int i=0;i<file->nmeshes;i++)
		{
			o.meshIDs.insert(i);
		}
		objects.push_back(o);
		saveObject(0,output);
	}

	void My3dsLoader::saveObject(int index, const char* fname)
	{
		Lib3dsFile *obj = lib3ds_file_new();
		obj->frames = file->frames;
		obj->master_scale = file->master_scale;

		//add materials
		for(int i=0;i<materialArray.size();i++)
		{
			Lib3dsMaterial * newMaterial =  lib3ds_material_new(materialArray[i].name);
			memcpy(newMaterial,&materialArray[i],sizeof(Lib3dsMaterial));
			lib3ds_file_insert_material(obj,newMaterial,-1);
		}

		//add root node
		Lib3dsMesh *meshModel = lib3ds_mesh_new("$$$DUMMY");
		Lib3dsMeshInstanceNode *model = lib3ds_node_new_mesh_instance( meshModel, objects[index].label.c_str(), NULL, NULL, NULL);
		lib3ds_file_insert_mesh(obj, meshModel, -1);
		lib3ds_file_append_node(obj, (Lib3dsNode*)model, NULL);
		
		//add children
		for(std::set<int>::iterator it = objects[index].meshIDs.begin(); it!=objects[index].meshIDs.end();++it)
		{
			Lib3dsNode *node = lib3ds_file_node_by_id(file, *it);
			if(node->type != LIB3DS_NODE_MESH_INSTANCE) continue;
			
			Lib3dsMesh* mesh = lib3ds_file_mesh_for_node(file,node);
			if(!mesh || !mesh->nvertices) continue;

			float (*orig_vertices)[3];
			orig_vertices = (float(*)[3])malloc(sizeof(float) * 3 * mesh->nvertices);
			memcpy(orig_vertices, mesh->vertices, sizeof(float) * 3 * mesh->nvertices);
			{
				float inv_matrix[4][4], M[4][4];

				lib3ds_matrix_copy(M, node->matrix);
				lib3ds_matrix_translate(M, -((Lib3dsMeshInstanceNode*)node)->pivot[0], 
																-((Lib3dsMeshInstanceNode*)node)->pivot[1],
																-((Lib3dsMeshInstanceNode*)node)->pivot[2]);
				lib3ds_matrix_copy(inv_matrix, mesh->matrix);
				lib3ds_matrix_inv(inv_matrix);
				lib3ds_matrix_mult(M, M, inv_matrix);

				for (int i = 0; i < mesh->nvertices; ++i) {
					float tmp[3];
					lib3ds_vector_transform(tmp, M, mesh->vertices[i]);
					lib3ds_vector_copy(mesh->vertices[i], tmp);
				}
			}
			
			Lib3dsMesh *newMesh = lib3ds_mesh_new(mesh->name);
			
			lib3ds_mesh_resize_vertices(newMesh, mesh->nvertices, mesh->texcos!=NULL, mesh->vflags != NULL);
			lib3ds_mesh_resize_faces(newMesh,mesh->nfaces);

			memcpy(newMesh->vertices, mesh->vertices, mesh->nvertices*3*sizeof(float));
			if(mesh->texcos!=NULL)
				memcpy(newMesh->texcos, mesh->texcos, mesh->nvertices*2*sizeof(float));
			if(mesh->vflags!=NULL)
				memcpy(newMesh->vflags, mesh->vflags, mesh->nvertices*sizeof(unsigned short));
			memcpy(newMesh->faces,mesh->faces,mesh->nfaces*sizeof(Lib3dsFace));

			lib3ds_file_insert_mesh(obj, newMesh, -1);
			Lib3dsMeshInstanceNode *inst = lib3ds_node_new_mesh_instance(newMesh, ((Lib3dsMeshInstanceNode*)node)->instance_name, NULL, NULL, NULL);
			lib3ds_file_append_node(obj, (Lib3dsNode*)inst, (Lib3dsNode*)model);

			memcpy(mesh->vertices, orig_vertices, sizeof(float) * 3 * mesh->nvertices);
			free(orig_vertices);
		}

		if (!lib3ds_file_save(obj, fname)) 
		{
			std::cerr << "ERROR: Saving 3ds file failed!\n";
			exit(-1);
		}
		lib3ds_file_free(obj);
	}

	void My3dsLoader::toObj(const char* fname)
	{
		std::ofstream out(fname);
		for(int i=0;i<vectexArray.size();i++)
			out << "v " << vectexArray[i][0] << " " << vectexArray[i][1] << " " << vectexArray[i][2] << std::endl;

		for(int i=0;i<faceArray.size()/3;i++)
			out << "f " << faceArray[i*3]+1 << " " << faceArray[i*3+1]+1 << " " << faceArray[i*3+2]+1 << std::endl;

		out.close();
	}

	void My3dsLoader::toOff(const char* fname)
	{
		std::ofstream out(fname);
		out << "OFF" << endl
			   << vectexArray.size() << " " << faceArray.size() <<  " " << 0 << endl; 

		for(int i=0;i<vectexArray.size();i++)
			out  << vectexArray[i][0] << " " << vectexArray[i][1] << " " << vectexArray[i][2] << std::endl;

		for(int i=0;i<faceArray.size()/3;i++)
			out << "3 " << faceArray[i*3] << " " << faceArray[i*3+1] << " " << faceArray[i*3+2] << std::endl;

		out.close();
	}

	void My3dsLoader::setName(std::string name)
	{
		this->name = name;
	}

	std::string My3dsLoader::getName()
	{
		return name;
	}

	void My3dsLoader::setOrientation(float x,float y,float z)
	{
		orientation[0] = x;
		orientation[1] = y;
		orientation[2] = z;
	}

	MyVector3D My3dsLoader::getOrientation()
	{
		return orientation;
	}
}