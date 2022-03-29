module twomux(
    input wire [5:0] a0, a1,
    input wire ctrlVar,

    output reg [5:0] otp
);

always@ ( * ) begin
    case (ctrlVar)
        0: otp = a0;
        1: otp = a1;
        default: otp = 0;
    endcase
end

endmodule