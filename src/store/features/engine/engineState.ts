import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { fields } from "../../../lib/events/eventActorCollisionsDisable";

export type EnginePropCType = "UBYTE" | "UWORD" | "BYTE" | "WORD";

export type EnginePropSchemaField = {
  key: string;
  label: string;
  group: string;
  type: EnginePropCType;
  defaultValue: any;
};

export interface EngineState {
  fields: EnginePropSchemaField[];
}

export const initialState: EngineState = {
  fields: [],
};

const engineSlice = createSlice({
  name: "engine",
  initialState,
  reducers: {
    setEngineFields: (
      state,
      action: PayloadAction<EnginePropSchemaField[]>
    ) => {
      state.fields = action.payload;
    },
  },
});

export const { actions, reducer } = engineSlice;

export default reducer;
