#include "../include/GLSLprog.h"
#include<fstream>
#include<vector>
namespace gameEngine{

    GLSLprog::GLSLprog() : _progID(0), _vsID(0), _fsID(0), _nAttrib(0)
    {
        //ctor
    }

    GLSLprog::~GLSLprog()
    {
        //dtor
    }

    void GLSLprog::compileShader( const std::string& vs_Path, const std::string& fs_Path ){
        //created id for the required shader. Here Vertex Shader (contains information about points)
        _vsID = glCreateShader(GL_VERTEX_SHADER);

        if(_vsID == 0)
            fatalError("Vertex shader could not be created!");
        //creates id for the fragment shader (sends the color information for a vertex to window )
        _fsID = glCreateShader(GL_FRAGMENT_SHADER);

        if(_fsID == 0)
            fatalError("Fragment shader could not be created!");

        compileShader(vs_Path, _vsID);
        compileShader(fs_Path, _fsID);

    }

    GLuint GLSLprog::getUniformLocation (const std::string& uniformName){
        //queries the specified uniform variable under mentioned program ID and assigns a number to that variable and return that number (4 byte unsigned integer)
        GLuint location = glGetUniformLocation(_progID, uniformName.c_str());

        if(location == GL_INVALID_INDEX)
            fatalError("Uniform " + uniformName + " can't be found!");

        return location;
    }

    void GLSLprog::linkShader(){

        //Vertex and fragment shaders are successfully compiled.
        //Now time to link them together into a program.
        //Get a program object.
        _progID = glCreateProgram();

        //Attach our shaders to our program
        glAttachShader(_progID, _vsID);
        glAttachShader(_progID, _fsID);

        //Link our program
        glLinkProgram(_progID);

        //ERROR CHECKING (OPTION BUT SHOULD BE USED)
        //Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_progID, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_FALSE){
            GLint maxLength = 0;
            glGetProgramiv(_progID, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(_progID, maxLength, &maxLength, &infoLog[0]);

            //We don't need the program anymore.
            glDeleteProgram(_progID);
            //Don't leak shaders either.
            glDeleteShader(_vsID);
            glDeleteShader(_fsID);

            //Use the infoLog as you see fit.

            //In this simple pogram, we'll just leave

            std::printf("%s\n", &infoLog[0]);
            fatalError("Shaders failed to link");
        }

        //Always detach shaders after a successful link.
        glDetachShader(_progID, _vsID);
        glDetachShader(_progID, _fsID);
        glDeleteShader(_vsID);
        glDeleteShader(_fsID);
    }

    void GLSLprog::addAttrib(const std::string& attribName){
        //adds a attribute or variable to the processed in shader code
        glBindAttribLocation(_progID, _nAttrib++, attribName.c_str());
    }

    void GLSLprog::compileShader(const std::string& filePath, GLuint id){

         //VERTEX SHADER COMPILATION BEGINS

        std::ifstream File(filePath);

        if(File.fail())
            fatalError(filePath + " could not be found");
        //string to store the contents of shader program in a single line
        std::string fileContent = "";
        //string to store one line of the shader program
        std::string line;

        while(std::getline(File,line)){

            fileContent += line +"\n";
        }

        File.close();

        const char* contentptr = fileContent.c_str();

        //replaces the source code in shader id with the shrader code
        //takes id, no. of elements in string and length array, pointer  to first element of string, length of string
        //as the code is in one line we just need to pass one string
        glShaderSource(id, 1, &contentptr, nullptr);

        //compiles the shader code
        glCompileShader(id);

        //error checking

        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if(success == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(id); // Don't leak the shader.

            std::printf("%s\n", &errorLog[0]);
            fatalError("Shader " + filePath + " failed to compile");
        }

        //error checking ends


    }



    void GLSLprog::use(){
        //installs  a program object in current rendering state
        glUseProgram(_progID);
        //enables generic vertex atrribute array to currently bound vao.
        for(int i=0; i<_nAttrib; i++)
            glEnableVertexAttribArray(i);
    }

    void GLSLprog::unuse(){
        //removes object from current rendering state
        glUseProgram(0);
        //disables generic vertex atrribute array to currently bound vao.
        for(int i=0; i<_nAttrib; i++)
            glDisableVertexAttribArray(i);
    }
}
