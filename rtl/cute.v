/* verilator lint_off PINMISSING */
// -----------------------------------------------------------------------------
// Cute-Processor
// -----------------------------------------------------------------------------
module cute(
    // -------------------------------------------------------------------------
    // Inputs
    // -------------------------------------------------------------------------
    input wire clk,
    input wire [8:0] DIN,
    input wire Resetn,
    input wire Run,
    // -------------------------------------------------------------------------
    // Outputs
    // -------------------------------------------------------------------------
    output reg done,
    //reg [8:0] a1, a2, a3, a4, a5, a6, a7, a8,
    output reg signed [8:0] bus,
    output reg jmp
    
);

// -----------------------------------------------------------------------------
// Internal wires
// -----------------------------------------------------------------------------

reg signed [8:0] a1, a2, a3, a4, a5, a6, a7, a8; // registers output
wire signed [8:0] aluo,Ao,Go; // logic outputs
wire [3:0] mux; // mux control input
wire A, G, alu; // enable logic
wire [7:0] rx; // enable registers


initial begin
assign a1 = 9'd50;
assign a2 = 9'd120;
assign a3 = 9'd80;
assign a4 = 9'd200;
assign a5 = 9'd68;
assign a6 = 9'd250;
assign a7 = 9'd8;
assign a8 = 9'd150;
end 


// -----------------------------------------------------------------------------
// Instanciate processor components
// -----------------------------------------------------------------------------

// Instanciate 8 memory registers
regn R1( .clk, .enable (rx[7]), .a0 (bus), .reg0 (a8) );
regn R2( .clk, .enable (rx[6]), .a0 (bus), .reg0 (a7) );
regn R3( .clk, .enable (rx[5]), .a0 (bus), .reg0 (a6) );
regn R4( .clk, .enable (rx[4]), .a0 (bus), .reg0 (a5) );
regn R5( .clk, .enable (rx[3]), .a0 (bus), .reg0 (a4) );
regn R6( .clk, .enable (rx[2]), .a0 (bus), .reg0 (a3) );
regn R7( .clk, .enable (rx[1]), .a0 (bus), .reg0 (a2) );
regn R8( .clk, .enable (rx[0]), .a0 (bus), .reg0 (a1) );

cufsm ControlUnitFSM(.ir (DIN), .Run, .Resetn, .clk, .a (A), .g (G), .mux, .alu, 
                        .rx, .done, .jmp);
    
mux Multiplexer(.a0 (DIN), .a1, .a2, .a3, .a4, .a5, .a6, .a7, .a8, .a9 (Go), .ctrlVar (mux), .otp (bus));

regn regA( .clk, .enable (A), .a0 (bus), .reg0 (Ao) );

regn regG( .clk, .enable (G), .a0 (aluo), .reg0 (Go) );

alu ArithmeticLogicUnit( .a (Ao), .b (bus), .c (aluo), .op (alu) );


endmodule
// -----------------------------------------------------------------------------