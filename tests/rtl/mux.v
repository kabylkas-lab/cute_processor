// ------------------------------------------------------------------------------------------
// 10 to 1 9-bit Multiplexer
// ------------------------------------------------------------------------------------------
module mux(
    // ----------------------------------------------------------------------------------
    // Inputs
    // ----------------------------------------------------------------------------------
    input wire signed [8:0] a0,
    input wire signed [8:0] a1,
    input wire signed [8:0] a2,
    input wire signed [8:0] a3,
    input wire signed [8:0] a4,
    input wire signed [8:0] a5,
    input wire signed [8:0] a6,
    input wire signed [8:0] a7,
    input wire signed [8:0] a8,
    input wire signed [8:0] a9,
    input wire [3:0] ctrlVar,
    // ----------------------------------------------------------------------------------
    output reg signed [8:0] otp        // output
    );

// ------------------------------------------------------------------------------------------
// Input selection by control inputs
// ------------------------------------------------------------------------------------------
always@( * )
    begin
    case(ctrlVar)
    4'b0000: otp=a0;
    4'b0001: otp=a1;
    4'b0010: otp=a2;
    4'b0011: otp=a3;
    4'b0100: otp=a4;
    4'b0101: otp=a5;
    4'b0110: otp=a6;
    4'b0111: otp=a7;
    4'b1000: otp=a8;
    4'b1001: otp=a9;
    default: otp=9'b000000000;
    endcase    
end
// ------------------------------------------------------------------------------------------
endmodule
// ------------------------------------------------------------------------------------------
