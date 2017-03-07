#ifndef GLSLPROG_H
#define GLSLPROG_H

#include<string>
#include<glew.h>
#include<Errors.h>
namespace gameEngine{

    class GLSLprog
    {
        public:
            GLSLprog();
            virtual ~GLSLprog();

            void compileShader( const std::string& vs_Path, const std::string& fs_Path );

            void linkShader();

            void addAttrib(const std::string& attribName);

            void use();

            void unuse();

            GLuint getUniformLocation (const std::string& uniformName);

        protected:
        private:

            void compileShader(const std::string& filePath, GLuint id);

            GLuint _progID;
            GLuint _vsID;
            GLuint _fsID;
            int _nAttrib;
    };
}
#endif // GLSLPROG_H
