module alu #(parameter WORD_SIZE = 8) (
  //data input
  input     [WORD_SIZE-1:0]   a,
  input     [WORD_SIZE-1:0]   b,

  //data output
  output    [WORD_SIZE-1:0]   c,

  //control input
  input                       op
);

  reg [WORD_SIZE-1:0] c_internal;

  always @(*) begin: alu_code
    if (op == 0) begin
      c_internal = a + b;
    end else begin
      c_internal = a - b;
    end
  end //alu_code

  assign c = c_internal;

endmodule
