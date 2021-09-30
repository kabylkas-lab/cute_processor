module m81(output out, input a, b, c, d, e, f, g, h, i, j, c1, c2, c3, c4);
assign c1bar=~c1;
assign c2bar=~c2;
assign c3bar=~c3;
assign c4bar=~c4;
assign otp = (a & c1bar & c2bar & c3bar & c4bar) | (b & c1bar & c2bar & c3bar & c4) | (c & c1bar & c2bar & c3 & c4bar) + (d & c1bar & c2bar & c3 & c4) + (e & c1bar & c2 & c3bar & c4bar) + (f & c1bar & c2 & c3bar & c4) + (g & c1bar & c2 & c3 & c4bar) + (h & c1bar & c2 & c3 & c4) + (i & c1 & c2bar & c3bar & c4bar) + (j & c1 & c2bar & c3bar & c4);
endmodule