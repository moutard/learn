#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include <string>
#include "core/mesh.h"
#include "utils/hgexception.h"

class MeshFactory
{
public:
    MeshFactory();
    std::string findExtension(const std::string & filename);
    void fromFile(const std::string & filename, Mesh * mesh);
    void fromOffFile(const std::string & filename, Mesh * mesh);
};

#endif // MESHFACTORY_H
