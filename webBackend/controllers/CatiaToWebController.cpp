#include "CatiaToWebController.h"


// 处理GET请求
void CatiaToWebController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    // 处理GET请求逻辑
    // 获取id参数并执行相应的操作
    // 构造 HTTP 响应对象
    auto resp = HttpResponse::newHttpResponse();

    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addHeader("Access-Control-Allow-Methods", "GET, PUT, POST, DELETE, OPTIONS");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type");

    // 读取CATIA文件
    std::string catiaFilePath = "C:/Users/KINPC/Desktop/Part1.stp";
    std::cout << "Reading CATIA file: " << catiaFilePath << std::endl;
    TopoDS_Shape shape = ReadSTEPFile(catiaFilePath);

    // 将CATIA文件转换为中间格式（例如ASSIMP）
    std::string intermediateFilePath = ConvertToIntermediateFormat(shape);
    std::cout << "Converting to intermediate format: " << intermediateFilePath << std::endl;

    // 将中间格式转换为GLTF格式
    std::string gltfFilePath = ConvertToGLTF(intermediateFilePath);
    std::cout << "Converting to GLTF format: " << gltfFilePath << std::endl;

    // 设置 HTTP 响应头和正文
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    resp->setBody(gltfFilePath);

    // 调用回调函数返回 HTTP 响应
    callback(resp);

}



// 读取 STEP 文件
TopoDS_Shape CatiaToWebController::ReadSTEPFile(const std::string& filePath)
{
    TopoDS_Shape shape;
    BRep_Builder builder;

    std::cout << "Reading STEP file: " << filePath << std::endl;

    if (!BRepTools::Read(shape, filePath.c_str(), builder))
    {
        std::cout << "Failed to read STEP file." << std::endl;
        // 可以在这里添加适当的错误处理逻辑
        // 比如日志记录或返回错误状态等
    }
    else
    {
        std::cout << "STEP file read successfully." << std::endl;
    }

    // 如果您知道 STEP 文件中包含的是实体（Solid），可以将结果转换为 TopoDS_Solid
    // 否则，可以直接使用 TopoDS_Shape

    TopoDS_Solid solid;
    if (shape.IsNull() || !shape.ShapeType() == TopAbs_SOLID)
    {
        std::cout << "Invalid shape type. Expecting a solid." << std::endl;
        // 如果无法将结果转换为实体（Solid），可以在这里添加适当的错误处理逻辑
        // 比如日志记录或返回错误状态等
    }
    else
    {
        solid = TopoDS::Solid(shape);
    }

    return solid;
}


// 读取CATIA文件，返回TopoDS_Shape对象
TopoDS_Shape CatiaToWebController::ReadCATIAFile(const std::string& filePath)
{
    TopoDS_Shape shape;
    BRep_Builder builder;
    if (!BRepTools::Read(shape, filePath.c_str(), builder))
    {
        LOG_ERROR << "Failed to read CATIA file.";
        // 可以在错误情况下返回适当的错误响应
    }
    return shape;
}


// 将CATIA文件转换为中间格式（例如ASSIMP），返回中间格式文件路径
std::string CatiaToWebController::ConvertToIntermediateFormat(const TopoDS_Shape& shape)
{
    // 假设你使用ASSIMP来进行转换
    Assimp::Exporter exporter;
    aiScene scene;
    // 在这里执行将CATIA数据填充到aiScene的代码
    // ...

    // 调用Assimp的导出函数，将数据转换为中间格式
    const aiExportDataBlob* blob = exporter.ExportToBlob(&scene, "assimp_format");
    if (!blob)
    {
        LOG_ERROR << "Failed to convert to intermediate format.";
        // 可以在错误情况下返回适当的错误响应
        return "";
    }

    // 将中间格式数据写入临时文件
    std::string intermediateFilePath = "C:/Users/KINPC/Desktop";
    std::ofstream file(intermediateFilePath, std::ios::binary);
    file.write(static_cast<const char*>(blob->data), blob->size);
    file.close();

    return intermediateFilePath;
}


// 将中间格式转换为GLTF格式，返回GLTF文件路径
std::string CatiaToWebController::ConvertToGLTF(const std::string& intermediateFilePath)
{
    // 调用Assimp的导入函数，读取中间格式数据
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(intermediateFilePath, aiProcess_Triangulate | aiProcess_GenNormals);
    if (!scene)
    {
        LOG_ERROR << "Failed to convert to GLTF.";
        // 可以在错误情况下返回适当的错误响应
        return "";
    }

    // 调用Assimp的导出函数，将数据转换为GLTF格式
    Assimp::Exporter exporter;
    std::string gltfFilePath = "C:/Users/KINPC/Desktop/output_file.gltf";
    exporter.Export(scene, "gltf2", gltfFilePath.c_str(), aiProcess_Triangulate | aiProcess_GenNormals);

    LOG_DEBUG << "Conversion to GLTF successful.";
    return gltfFilePath;
}
