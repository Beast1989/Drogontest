// TopToolbar.js
import React from "react";

const topToolbarStyles = {
  container: {
    height: "10%",
    backgroundColor: "lightgray",
    // 其他样式属性...
  },
};

function TopToolbar() {
  return (
    
    <div style={topToolbarStyles.container}>
      {/* TopToolbar的内容 */}
      <h1>Top Toolbar</h1>
    </div>
  );
}

export default TopToolbar;
