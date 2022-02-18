// -----------------------------------------------------------------------------
// FSM
// -----------------------------------------------------------------------------
module cufsm(
    // -------------------------------------------------------------------------
    // Inputs
    // -------------------------------------------------------------------------
    input wire [8:0] ir,
    input wire Resetn,
    input wire clk,

    // -------------------------------------------------------------------------
    // Outputs
    // -------------------------------------------------------------------------
    output reg a,
    output reg g,
    output reg [3:0] mux,
    output reg alu,
    output reg [7:0] rx,
    output reg done
    // -------------------------------------------------------------------------

    );

localparam STATE_Initial = 3'd0,
    STATE_alu1 = 3'd1, // alu = 0
    STATE_alu2 = 3'd2, 
    STATE_alu3 = 3'd3,
    STATE_mv1 = 3'd4,
    STATE_5_PlaceHolder = 3'd5;
    //STATE_6_placeHolder = 3'd6,
    //STATE_7_PlaceHolder = 3'd7;


reg [2:0] CurrentState;
reg [2:0] NextState;

reg [2:0] cmd;
reg [2:0] adr1;
reg [2:0] adr2;

assign cmd = ir[6+:3];
assign adr1 = ir[3+:3];
assign adr2 = ir[0+:3];


// -----------------------------------------------------------------------------
// Conditional State - Transition
// -----------------------------------------------------------------------------

always@ ( posedge clk ) begin
    if ( Resetn || done ) begin
        CurrentState <= STATE_Initial;
    end else CurrentState <= NextState;
end


always@ ( * ) begin
    NextState = CurrentState ;
    case ( CurrentState )
        STATE_Initial : begin
            a = 0;
            g = 0;
            rx = 8'd0;
            mux = 4'd0;
            alu = 0;
            done = 0;
            if (cmd[1]) NextState = STATE_mv1;
            else NextState = STATE_alu1;
        end
        STATE_alu1 : begin
            mux = adr1+1;
            rx[adr1] = 1;
            a = 1;
            
            NextState = STATE_alu2;
            done = 0;
        end
        STATE_alu2 : begin
            rx[adr1] = 0;
            mux = adr2 + 1;
            rx[adr2] = 1;
            alu = cmd[0];
            a = 1;
            g = 1;
            NextState = STATE_alu3;
            done = 0;
        end
        STATE_alu3 : begin
            a = 0;
            rx[adr2] = 0;
            alu = 0;
            mux = 4'd9;
            g = 1;
            rx[adr1] = 1;
            done = 1;
        end
        STATE_mv1 : begin
            mux = adr1 +1;
            rx[adr1] = 1;
            rx[adr2] = 1;
            done = 1;
        end
        STATE_5_PlaceHolder: begin
            if (cmd[2]) NextState = STATE_Initial;
            else NextState = STATE_Initial;
        end
        /*STATE_6_PlaceHolder : begin
            NextState = STATE_Initial;
        end
        STATE_7_PlaceHolder : begin
            NextState = STATE_Initial;
        end*/
        default : begin
            NextState = STATE_Initial;
        end
    endcase
end
// -----------------------------------------------------------------------------

endmodule
// -----------------------------------------------------------------------------
