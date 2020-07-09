#include "mesh.hh"

#include <llama/type.hh>
#include <llama/resource_loader.hh>

#include <glm/glm.hpp>

#include <sstream>
#include <vector>
#include <unordered_map>

#include <iostream>

struct indexed_vertex_representation
{
	uint32 v, n, uv;

	bool operator==(const indexed_vertex_representation & ivr) const
	{
		return this->v == ivr.v && this->n == ivr.n && this->uv == ivr.uv;
	}

};

struct ivr_hash_functor
{
	uint64 operator()(const indexed_vertex_representation & ivr) const
	{
		return ivr.v + ivr.n << 1 + ivr.uv << 2;
	}
};

struct intermediate_face_representation
{
	// @Note : We are assuming that obj files are
	// only triangle based
	indexed_vertex_representation vertices[3];
};

// @Fixme : This is for debugging purposes only

std::ostream & operator<<(std::ostream & stream, const indexed_vertex_representation & ivr)
{
	stream << "{" << ivr.v << "," << ivr.n << "," << ivr.uv << "}";
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const intermediate_face_representation & ifr)
{
	stream << "{" << ifr.vertices[0] << "," << ifr.vertices[1] << "," << ifr.vertices[2] << "}";
	return stream;
}

void * llama_load_mesh(char * filename)
{
	char * ptr = llama_load_file_buffer(filename);

	if(ptr == nullptr) return {};

	// reading from a obj file

	std::stringstream ss(ptr);

	std::string line;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	std::vector<intermediate_face_representation> faces;

	// reading a space seperated line read buffer
	while(ss >> line)
	{
		if(line == "v")
		{
			real32 x, y, z;
			ss >> x >> y >> z;

			vertices.push_back(glm::vec3(x, y, z));
		}
		else if(line == "vn")
		{
			real32 x, y, z;
			ss >> x >> y >> z;

			normals.push_back(glm::vec3(x, y, z));
		}
		else if(line == "uv")
		{
			real32 x, y;
			ss >> x >> y;

			uvs.push_back(glm::vec2(x, y));
		}
		else if(line == "f")
		{
			// when we parse faces all the other information
			// normals, vertices and uvs are already in the
			// vectors
	
			intermediate_face_representation ifr;

			for(int64 i = 0 ; i < 3 ; i++)
			{

				std::string internal_line;
				ss >> internal_line;

				uint32 arr[3] = {0};

				std::stringstream edge(internal_line);

				for(int32 j = 0 ; j < 3 ; j++)
				{
					std::getline(edge, line, '/');
	
					if(line.size() == 0) arr[j] = 0;

					arr[j] = std::stoi(line);
				}

//				std::cout << "  faceinformation : " <<  arr[0] << " " << arr[1] << " " << arr[2] << "\n";

				ifr.vertices[i] = {arr[0], arr[1], arr[2]};
	
			}
//			std::cout << " " << ifr << "\n";

			faces.push_back(ifr);
		}
	}

	llama_unload_file_buffer(ptr);

//	std::cout << "buffer pointer unloaded \n";
	// creating a index array for mesh
	
	
	std::unordered_map<indexed_vertex_representation, uint32, ivr_hash_functor> vertex_index_pair;

//	std::cout << "iterating over every face \n";

	uint32 counter = 0;

	std::vector<uint32> index_data;

	for(auto face : faces)
	{
		for(int8 i = 0 ; i < 3 ; i++)
		{
			auto it = vertex_index_pair.find(face.vertices[i]);
			// element not there 
			if(it  == vertex_index_pair.end())
			{
				vertex_index_pair[face.vertices[i]] = counter;
				index_data.push_back(counter);

				counter+=1 ;
			}
			else 
			{
//				std::cout << "  it->second " << it->second << "\n";
				index_data.push_back(it->second);
			}
		}
	}

//	std::cout << "vertex index pairs found (size : " << vertex_index_pair.size() << ") \n"; 


	// creating vertices array

	std::vector<Vertex> vertex_data;


	for(auto it = vertex_index_pair.begin() ; it != vertex_index_pair.end(); it++)
	{
		Vertex vertex;
		vertex.pos    = vertices[it->first.v - 1];
		vertex.normal = vertices[it->first.n - 1];
		vertex.uv     = vertices[it->first.uv - 1];

		vertex_data.push_back(vertex);
	}


	Mesh * meshptr = new Mesh;

	meshptr->vertex_count = vertex_data.size();
	meshptr->index_count  = index_data.size();

	meshptr->vertices = new Vertex[vertex_data.size()];
	meshptr->indices  = new uint32[index_data.size()];

	for(int64 i = 0 ; i < vertex_data.size() ; i++) meshptr->vertices[i] = vertex_data[i];
	
	for(int64 i = 0 ; i < index_data.size() ; i++) meshptr->indices[i] = index_data[i];

	return meshptr;
}

void llama_unload_mesh(void * meshptr)
{
	if(meshptr == nullptr) return;

	Mesh * mesh = (Mesh *) meshptr;

	delete mesh->vertices;
	delete mesh->indices;

	mesh->vertices = nullptr;
	mesh->indices  = nullptr;
	
	mesh->vertex_count = 0;
	mesh->index_count  = 0;

	delete mesh;
}
