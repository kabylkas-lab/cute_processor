// -----------------------------------------------------------------------------
// Instruction memory
// -----------------------------------------------------------------------------
/* verilator lint_off WIDTH */
module com(
    input wire clk,
    //input wire Run,
    input wire Resetn,

    output reg signed [8:0] bus,

reg [8:0] DIN,
reg [5:0] aluo,
reg [5:0] Z,
    reg Run,

    output reg done
    
);

// Processor
//reg [8:0] DIN;

// ALU
reg add;
//reg [3:0] aluo;
//assign aluo = 4'd0;
assign add = 0;

// MUX
reg [5:0] address;
wire ctrlVar;
wire [5:0] otp;

//reg [3:0] Z;

regn ALU_reg( .clk, .enable (done), .a0 (otp), .reg0 (Z) );

alu ArithmeticLogicUnit( .a (Z), .b (done), .c (aluo), .op (add) );

twomux TwoToOneMultiplexer( .a0 (aluo), .a1 (address), .ctrlVar, .otp );

reg [8:0] mem [0:9];
integer     fd;  
   

integer i; 

initial begin  
    fd = $fopen("/home/terrofont/cute_processor/cmd/instructions.txt", "r");  
    i = 0; 
    while (! $feof(fd)) begin  
        $fscanf(fd,"%b\n",mem[i]);
        i=i+1;
    end
    $fclose(fd);  
end
//assign mem[0] = 9'b011000110;
//assign mem[1] = 9'b011001001;
//assign mem[2] = 9'b011010101;
//assign mem[3] = 9'b011011010;
//assign a5 = 9'd68;
//assign a6 = 9'd250;
//assign a7 = 9'd8;
//assign a8 = 9'd300;
/*
assign mem[0] = 9'b001000001;
assign mem[1] = 9'b001000001;
assign mem[2] = 9'b000010011;
assign mem[3] = 9'b011000011;
assign mem[4] = 9'b001111011;
assign mem[5] = 9'b000101100;
assign mem[6] = 9'b010100101;
assign mem[7] = 9'b100000000;;
assign mem[8] = 9'b100000000;
*/

always@ ( posedge clk )  begin
    if ( Resetn || done ) begin
        Run <= 0;
    end
    else begin 
        Run <= 1;
    end
    address <= bus[5:0];
    if (Run) DIN <= mem[aluo];
end



cute CuteProcessor(.clk, .DIN, .Resetn, .Run, .done, .bus, .jmp (ctrlVar) );

endmodule
// -----------------------------------------------------------------------------