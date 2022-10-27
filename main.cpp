#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

#include <vector>
#include <string>
#include <fstream>

int i = 0;
bool toggle;
std::string fileNameArg;
int numberOfFiles;

// Initialize polyscope

//
void loadOBJ(const std::string file_name, std::vector<std::vector<float>>& meshVerts, std::vector<std::vector<unsigned int>>& meshFaces)
{
    std::stringstream ss;
    std::ifstream in_file(file_name.c_str());

    if(!in_file.is_open())
    {
        std::cerr<<"Couldn't open the file\n";
    }

    std::string line;
    std::string prefix = "";
    unsigned int temp = 0;

    while(std::getline(in_file, line))
    {
        ss.clear();
        ss.str(line);
        ss >> prefix;

        std::vector<float> tempVerts;
        std::vector<unsigned int> tempFaces;

        if(prefix == "#")
        {

        }

        else if ( prefix == "v" )
        {
            float x,y,z;
            ss >> x >> y >> z;
            tempVerts.push_back(x);
            tempVerts.push_back(y);
            tempVerts.push_back(z);
            meshVerts.push_back(tempVerts);
        }

        else if ( prefix == "f" )
        {
            int counter = 0;
            while (ss >> temp)
            {
                tempFaces.push_back(temp - 1);
                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                }
                if ( ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                }
                if (ss.peek() == ' ')
                {
                    ss.ignore(1, ' ');
                }

                // std::cout<<temp<<" , ";
            }
            // std::cout<<" \n";
            meshFaces.push_back(tempFaces);
        }
    }
}

void mySubroutine(int& i) {
    std::vector<std::vector<float>> meshVerts;
    std::vector<std::vector<unsigned int>> meshFaces;

    std::string file_name = fileNameArg + "/" + std::to_string(i) + ".obj";

    loadOBJ(file_name, meshVerts, meshFaces);

    polyscope::registerSurfaceMesh("my mesh", meshVerts, meshFaces);
}


// Your callback functions
void myCallback() {
    // Since options::openImGuiWindowForUserCallback == true by default, 
    // we can immediately start using ImGui commands to build a UI

    ImGui::PushItemWidth(100); // Make ui elements 100 pixels wide,
    // To go to previous frame
    if (ImGui::Button("Previous")) {
        i--;
        mySubroutine(i);
    }

    // Toggle play and pause
    ImGui::SameLine();
    if(toggle)
    {
        i++;
        mySubroutine(i);

        if (ImGui::Button("Pause")) {
            toggle = false;
        }
    }

    else {
        if (ImGui::Button("Play")) {
            i++;
            toggle = true;
        }
    }

    // To go to next frame
    ImGui::SameLine();
    if (ImGui::Button("Next")) {
        i++;
        mySubroutine(i);
    }

    // To go to frame 1
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        i = 0;
        mySubroutine(i);
    }

    if (ImGui::Button(std::string("Current: " + std::to_string(i)).c_str())) {
        polyscope::warning("hi");
    }

    ImGui::PopItemWidth();

    if( i > numberOfFiles || i < 0) 
    {
        i = 0;
    }
}


int main(int argc, char *argv[])
{
    polyscope::init();

    fileNameArg = std::string(argv[1]);
    numberOfFiles = std::atoi(argv[2]);
    toggle = false;

    polyscope::options::automaticallyComputeSceneExtents = false;
	polyscope::state::lengthScale = 1.;
	polyscope::state::boundingBox = std::tuple<glm::vec3, glm::vec3> { { -1., -3., -1. }, { 1., 1., 1. } };

    polyscope::state::userCallback = myCallback;

    polyscope::show();
}

