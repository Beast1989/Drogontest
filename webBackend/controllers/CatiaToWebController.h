
#include <drogon/HttpController.h>
#include <drogon/HttpClient.h>
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpSimpleController.h>

#include <TopoDS_Shape.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <Assimp/Importer.hpp>
#include <Assimp/Exporter.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include <STEPCAFControl_Reader.hxx>
#include <XSControl_WorkSession.hxx>
#include <XSControl_TransferReader.hxx>
#include <TopoDS.hxx>

using namespace drogon;

class CatiaToWebController : public HttpSimpleController<CatiaToWebController>
{
public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) override;

    PATH_LIST_BEGIN
        // ���崦��·��
        PATH_ADD("/test", Get);  // �����·����GET����
    PATH_LIST_END

    static TopoDS_Shape ReadCATIAFile(const std::string& filePath);

    // ��CATIA�ļ�ת��Ϊ�м��ʽ������ASSIMP���������м��ʽ�ļ�·��
    std::string ConvertToIntermediateFormat(const TopoDS_Shape& shape);

    // ���м��ʽת��ΪGLTF��ʽ������GLTF�ļ�·��
    std::string ConvertToGLTF(const std::string& intermediateFilePath);


    // ��ȡ STEP �ļ�
    TopoDS_Shape ReadSTEPFile(const std::string& filePath);
    // ��Ӹ��ദ����...
};
