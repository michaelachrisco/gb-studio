// See the Electron documentation for details on how to use preload scripts:
// https://www.electronjs.org/docs/latest/tutorial/process-model#preload-scripts

import { contextBridge, ipcRenderer, nativeTheme } from "electron";
import path from "path";
import l10n from "lib/helpers/l10n";
import { L10NAPI } from "lib/renderer/api/preload/l10nPreload";
import { API } from "lib/renderer/api/preload/apiPreload";

type JsonValue = string | number | boolean | null;

export const SplashAPI = {
  platform: process.platform,
  l10n: (key: string, params?: Record<string, string | number>) =>
    l10n(key, params),
  openExternal: (path: string) => ipcRenderer.invoke("open-external", path),
  theme: {
    getShouldUseDarkColors: () => nativeTheme?.shouldUseDarkColors,
    getThemeSetting: () => ipcRenderer.invoke("settings-get", "theme"),
    onChange: (callback: () => void) => {
      nativeTheme?.on("updated", callback);
      ipcRenderer?.on("update-theme", callback);
    },
  },
  path: {
    basename: (input: string) => path.basename(input),
    dirname: (input: string) => path.dirname(input),
    normalize: (input: string) => path.normalize(input),
    getDocumentsPath: () => ipcRenderer.invoke("get-documents-path"),
    chooseDirectory: (): Promise<string | undefined> =>
      ipcRenderer.invoke("open-directory-picker"),
  },
  settings: {
    get: (key: string) => ipcRenderer.invoke("settings-get", key),
    set: (key: string, value: JsonValue) =>
      ipcRenderer.invoke("settings-set", key, value),
  },

  project: {
    openProjectFilePicker: () => ipcRenderer.invoke("open-project-filepicker"),
    getRecentProjects: (): Promise<string[]> =>
      ipcRenderer.invoke("get-recent-projects"),
  },
} as const;

contextBridge.exposeInMainWorld("SplashAPI", SplashAPI);
contextBridge.exposeInMainWorld("L10NAPI", L10NAPI);
contextBridge.exposeInMainWorld("API", API);

export default contextBridge;