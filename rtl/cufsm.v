/* verilator lint_off UNOPTFLAT */
// -----------------------------------------------------------------------------
// CUFSM
// -----------------------------------------------------------------------------
module cufsm(
    // -------------------------------------------------------------------------
    // Inputs
    // -------------------------------------------------------------------------
    input wire [8:0] ir,
    input wire Run,
    input wire Resetn,
    input wire clk,

    input wire ZF,
    input wire SF,
    input wire OF,

    // -------------------------------------------------------------------------
    // Outputs
    // -------------------------------------------------------------------------
    output reg a,
    output reg g,
    output reg [3:0] mux,
    output reg alu,
    output reg [7:0] rx,
    output reg done,
    output reg jmp
    // -------------------------------------------------------------------------

    );


localparam STATE_Initial = 3'd0,
    STATE_alu1 = 3'd1, // add or sub instruction
    STATE_alu2 = 3'd2, 
    STATE_alu3 = 3'd3,
    STATE_mv1  = 3'd4,  // move instruction
    STATE_mvi  = 3'd5,  // move-immediate instruction
    STATE_jmp  = 3'd6;  // jump instruction

reg [2:0] CurrentState;
reg [2:0] NextState;

reg [2:0]  cmd;
reg [2:0] adr1;
reg [2:0] adr2;

reg [2:0] flag;

// 000 - ADD
// 001 - SUB
// 010 - MV
// 011 - MVI
// 100 - JMP
// 101 - CMP
// 110 - JGE
// 111 - JLE 

// -----------------------------------------------------------------------------
// Conditional State - Transition
// -----------------------------------------------------------------------------

always@ ( posedge clk ) begin
    if ( Resetn || done ) begin
        CurrentState <= STATE_Initial;
    end
    else begin 
        CurrentState <= NextState;
    end
end


always@ ( * ) begin
    if (Run) begin
        cmd = ir[6+:3];
        adr1 = ir[3+:3];
        adr2 = ir[0+:3];
    end
    NextState = CurrentState ;
    case ( CurrentState )
        STATE_Initial : begin
            a = 0;
            g = 0;
            rx = 8'd0;
            alu = 0;
            done = 0;
            mux = 0;
            jmp = 0;
            //if (ir != 9'd0 & Run) begin
            if (Run) begin
                if (cmd==3'b010)          NextState = STATE_mv1;
                else if (cmd[2:1]==2'b00) NextState = STATE_alu1; 
                else if (cmd==3'b101)     NextState = STATE_alu1; 
                else if (cmd==3'b011)     NextState = STATE_mvi;
                else if (cmd==3'b100)     NextState = STATE_jmp;
                else if (cmd[2:1]==2'b11) NextState = STATE_jmp;
            end
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
            if(cmd[2]==0) begin
                mux = 4'd9;
                g = 1;
                rx[adr1] = 1;
            end else begin
                flag[0] = OF;
                flag[1] = ZF;
                flag[2] = SF;
            end
            done = 1;
        end
        STATE_mv1 : begin
            mux = adr2+ 4'b0001;
            rx[adr1] = 1;
            rx[adr2] = 1;
            done = 1;
        end
        STATE_mvi: begin
            mux = 4'd0;
            rx[adr1] = 1;
            done = 1;
        end
        STATE_jmp: begin
            mux = 4'd0;
            if( cmd==3'b100 )  jmp = 1;
            if ( flag[2]==flag[0] & cmd[0]==0 ) jmp = 1;
            else if ( flag[1]==1  & cmd[0]==1 ) jmp = 1;
            else if ( flag[2]==1  & cmd[0]==1 ) jmp = 1;
            done = 1;
        end
        default : begin
            NextState = STATE_Initial;
        end
    endcase
end
// -----------------------------------------------------------------------------

endmodule
// -----------------------------------------------------------------------------