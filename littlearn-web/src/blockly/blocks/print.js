
import * as Blockly from 'blockly/core';

// Create a custom block called 'add_text' that adds
// text to the output div on the sample app.
// This is just an example and you should replace this with your
// own custom blocks.
const print = {
  'type': 'print',
  'message0': 'Print %1',
  'args0': [
    {
      'type': 'input_value',
      'name': 'TEXT',
      'check': 'Number',
    },
  ],
  'previousStatement': null,
  'nextStatement': null,
  'colour': 160,
  'tooltip': '',
  'helpUrl': '',
};

// Create the block definitions for the JSON-only blocks.
// This does not register their definitions with Blockly.
// This file has no side effects!
export const blocks2 = Blockly.common.createBlockDefinitionsFromJsonArray(
    [print]);
