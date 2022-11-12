import About from "components/app/About";
import React from "react";
import ReactDOM from "react-dom";
import { AppContainer } from "react-hot-loader";
import API from "lib/renderer/api";

const render = async () => {
  await API.l10nInit();
  ReactDOM.render(
    <AppContainer>
      <About />
    </AppContainer>,
    document.getElementById("App")
  );
};

render();

if (module.hot) {
  module.hot.accept(render);
}