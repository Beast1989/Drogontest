import React, { useEffect, useRef } from "react";
import * as BABYLON from "babylonjs";

const displayAreaStyles = {
  container: {
    height: "90%",
    backgroundColor: "white",
    // 其他样式属性...
  },
};

function DisplayArea() {
  const canvasRef = useRef(null);

  useEffect(() => {
    // 创建 Babylon.js 引擎和场景
    const canvas = canvasRef.current;
    const engine = new BABYLON.Engine(canvas, true);
    const scene = new BABYLON.Scene(engine);

    // 创建自由摄像机并设置位置和目标
    const camera = new BABYLON.FreeCamera(
      "camera",
      new BABYLON.Vector3(0, 0, -5),
      scene
    );
    camera.setTarget(BABYLON.Vector3.Zero());

    // 将摄像机附加到渲染的画布上
    camera.attachControl(canvas, true);

    // 在这里使用 Babylon.js API 加载和渲染模型
    // ...

    // 渲染场景
    engine.runRenderLoop(() => {
      scene.render();
    });

    return () => {
      // 在组件卸载时停止引擎
      engine.stopRenderLoop();
    };
  }, []);

  return (
    <div style={{ width: "100%", height: "100%" }}>
      <canvas
        ref={canvasRef}
        style={{ width: "100%", height: "100%" }}
        tabIndex={1}
      ></canvas>
    </div>
  );
}

export default DisplayArea;
