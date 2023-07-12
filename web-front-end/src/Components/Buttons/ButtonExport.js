import React from "react";
import { Button } from "@mui/material";
import styled from "styled-components";
const CustomButton = styled.button`
  width: auto;
  height: 26px;
  font-size: 11px;
  background-color: white;
  color: #0070ca;
  border: 1px solid #e0e0e0; /* 添加边框样式 */
  border-radius: 3px;
  margin-right: 3px;
  text-transform: none;
  /* 添加其他样式属性 */

  &:hover {
    background-color: #0070ca;
    color: white;
    /* 鼠标悬停时背景色变为蓝色，文字颜色为白色 */
  }

  &:active {
    background-color: #0070ca;
    color: white;
    /* 鼠标按下时背景色变为蓝色，文字颜色为白色 */
  }
`;
const ButtonExport = () => {
  const handleButtonClick = () => {
    // 按钮点击事件的处理逻辑
    console.log("ButtonExport按钮被点击了");
  };

  return (
    <CustomButton variant="contained" onClick={handleButtonClick}>
      Export
    </CustomButton>
  );
};

export default ButtonExport;
