module mux(otp, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, ctrlVar);
input [8:0] a0;
input [8:0] a1;
input [8:0] a2;
input [8:0] a3;
input [8:0] a4;
input [8:0] a5;
input [8:0] a6;
input [8:0] a7;
input [8:0] a8;
input [8:0] a9;
input [3:0] ctrlVar;
output reg [8:0] otp;

always@(*)
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
endmodule
