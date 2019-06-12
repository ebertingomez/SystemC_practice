module PGCD (
              input clk,
              input valid,
              input [7:0] a,
              input [7:0] b,
              output ready,
              output [7:0] pgcd
           );

logic [7:0] max, min;
wire [7:0] d = max-min;

always_ff @(posedge clk)
   if (valid)
   begin
      max <= (a>b)? a:b;
      min <= (a>b)? b:a;
   end
   else
   begin
      max <= (d>min)? d : min;
      min <= (d>min)? min : d;
   end

assign pgcd = max;
assign ready = (min==max);

endmodule