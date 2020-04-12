Blockly.JavaScript['ir_remote_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = `DEV_IO.IR(${dropdown_pin}).read()`;
	return [code, Blockly.JavaScript.ORDER_NONE];
};
