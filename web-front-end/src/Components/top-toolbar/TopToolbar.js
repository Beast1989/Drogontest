import React from "react";
import { Box } from "@mui/material";
import Button3DPoint from "../Buttons/Button3DPoint";
import ButtonPointOnCurve from "../Buttons/ButtonPointOnCurve";
import ButtonPointBetween from "../Buttons/ButtonPointBetween";
import ButtonSave from "../Buttons/ButtonSave";
import ButtonExport from "../Buttons/ButtonExport";
import "./TopToolbar.css";

const TopToolbar = () => {
  return (
    <Box display="flex" justifyContent="space-between" className="top-toolbar">
      <div className="section">
        <div className="button-row">
          <Button3DPoint />
          <ButtonPointOnCurve />
          <ButtonPointBetween />
          {/* 添加其他按钮 */}
        </div>
      </div>
      <div className="section">
        <div className="button-row">{/* 添加其他按钮 */}</div>
      </div>
      <div className="section">
        <div className="button-row">{/* 添加其他按钮 */}</div>
      </div>
      <div className="section">
        <div className="button-row">{/* 添加其他按钮 */}</div>
      </div>
      <div className="section">
        <div className="button-row">
          <ButtonSave />
          <ButtonExport />
          {/* 添加其他按钮 */}
        </div>
      </div>

      {/* 其他区域的内容... */}
    </Box>
  );
};

export default TopToolbar;
