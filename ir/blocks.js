Blockly.Blocks['ir_remote_read'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IR_REMOTE_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "IN1", "32" ]
				]
			}],
			"output": "Number",
			"colour": 135,
			"tooltip": Blockly.Msg.IR_REMOTE_READ_TOOLTIP,
			"helpUrl": "https://www.github.com/maxpromer/ir-remote"
		});
	}
};
