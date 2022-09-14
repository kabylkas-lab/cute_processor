module falu #(parameter width = 9) (
    // Data input.
    input                  clk,
    input      [width-1:0]   a,
    input      [width-1:0]   b,

    // Data output.
    output reg [width-1:0]   c,

    output reg              ZF, // Zero flag
    output reg              SF, // Sign flag
    output reg              OF, // Overflow flag

    // Control input.
    input                   op
);

reg [width-1:0] c_internal;

always @( * )
begin: alu_code
    if (op == 0) begin
        c_internal = a + b;
    end else begin
        c_internal = a - b;
    end
end //alu_code

assign c = c_internal;

always@ ( posedge clk) begin
case (c_internal)
    9'd0: ZF <= 1;
    default: ZF <= 0;
    endcase
    OF <= (c_internal[width-1]&!(a[width-1])&!(b[width-1])|!(c_internal[width-1])&(a[width-1])&(b[width-1]));
    SF <= c_internal[width-1];
end

endmodule
