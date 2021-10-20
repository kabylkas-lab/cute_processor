// -----------------------------------------------------------------------------
// FSM
// -----------------------------------------------------------------------------
module fsm(
	// -------------------------------------------------------------------------
	// Inputs
	// -------------------------------------------------------------------------
	input wire a,
	input wire Reset,
	input wire clk,

	// -------------------------------------------------------------------------
	// Outputs
	// -------------------------------------------------------------------------
	output reg unlck
	// -------------------------------------------------------------------------

	);

localparam STATE_Initial = 3'd0,
	STATE_1 = 3'd1,
	STATE_2 = 3'd2,
	STATE_3 = 3'd3,
	STATE_4 = 3'd4,
	STATE_5 = 3'd5,
	STATE_6 = 3'd6,
	STATE_7_PlaceHolder = 3'd7;


reg [2:0] CurrentState;
reg [2:0] NextState;


// -----------------------------------------------------------------------------
// Conditional State - Transition
// -----------------------------------------------------------------------------

always@ ( posedge clk ) begin
	if (Reset)
	CurrentState <= STATE_Initial ;
	else CurrentState <= NextState ;
end

always@ ( * ) begin
	NextState = CurrentState ;
	case ( CurrentState )
		STATE_Initial : begin
			if (!a) NextState = STATE_1;
		end
		STATE_1 : begin
			if (a) NextState = STATE_2;
			else NextState = STATE_Initial;
		end
		STATE_2 : begin
			if (!a) NextState = STATE_3;
			else NextState = STATE_Initial;
		end
		STATE_3 : begin
			if (a) NextState = STATE_4;
			else NextState = STATE_Initial;
		end
		STATE_4 : begin
			if (a) NextState = STATE_5 ;
			else NextState = STATE_Initial ;
		end
		STATE_5: begin
			unlck=1;
		end
		STATE_6: begin
			NextState = STATE_Initial;
		end
		/*
		STATE_6_PlaceHolder : begin
			NextState = STATE_Initial;
		end
		*/
		STATE_7_PlaceHolder : begin
			NextState = STATE_Initial;
		end
		default : begin
			unlck = 0;
		end
	endcase
end
// -----------------------------------------------------------------------------

endmodule
// -----------------------------------------------------------------------------
