module mux(otp, a, b, c, d, e, f, g, h, i, j, c1, c2, c3, c4);
input wire a, b, c, d, e, f, g, h, i, j, c1, c2, c3, c4;
output reg otp;

wire [3:0] select;
assign select = {c1, c2, c3, c4};
always@(*)
    begin
    case(select)
    4'b0000: otp=a;
    4'b0001: otp=b;
    4'b0010: otp=c;
    4'b0011: otp=d;
    4'b0100: otp=e;
    4'b0101: otp=f;
    4'b0110: otp=g;
    4'b0111: otp=h;
    4'b1101: otp=i;
    4'b1110: otp=j;
    default: otp=1'b0;
    endcase
end
endmodule
