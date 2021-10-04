module mux(otp, a, b, c, d, e, f, g, h, i, j, ctrlVar);
input wire a, b, c, d, e, f, g, h, i, j;
input [3:0] ctrlVar;
output reg otp;

always@(*)
    begin
    case(ctrlVar)
    4'b0000: otp=a;
    4'b0001: otp=b;
    4'b0010: otp=c;
    4'b0011: otp=d;
    4'b0100: otp=e;
    4'b0101: otp=f;
    4'b0110: otp=g;
    4'b0111: otp=h;
    4'b1000: otp=i;
    4'b1001: otp=j;
    default: otp=1'b0;
    endcase
end
endmodule
