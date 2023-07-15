
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
        // 定义处理路径
        PATH_ADD("/test", Get);  // 处理根路径的GET请求
    PATH_LIST_END

    static TopoDS_Shape ReadCATIAFile(const std::string& filePath);

    // 将CATIA文件转换为中间格式（例如ASSIMP），返回中间格式文件路径
    std::string ConvertToIntermediateFormat(const TopoDS_Shape& shape);

    // 将中间格式转换为GLTF格式，返回GLTF文件路径
    std::string ConvertToGLTF(const std::string& intermediateFilePath);


    // 读取 STEP 文件
    TopoDS_Shape ReadSTEPFile(const std::string& filePath);
    // 添加更多处理函数...
};
