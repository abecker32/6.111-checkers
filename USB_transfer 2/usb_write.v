//writes data from in
module usb_write(clk,reset,data,wr,txe,in,newin,hold,state, success);
	input clk, reset;	//clock and reset
	output [7:0] data;	//the data pins from the USB fifo
	input txe;			//the txe pin from the USB fifo
	output wr;			//the wr pin from the USB fifo
	reg wr;

	input[7:0] in;	//data to be written
	reg[7:0] in_stored; 	//stored version of in so it can't be changed during write
	input newin;		//when this is high, new data is ready to write
	input hold;			//as long as hold is high, this module holds
	
	output state;		//for debugging purposes
	reg[3:0] state;

	output reg success; //indicates write succeeded i.e. txe was low when called; goes high when write finishes
	
	parameter RESET 		= 0;		//state data
	parameter WAIT 			= 1;
	parameter WRITING		= 2;
	parameter WRITING_2		= 3;
	parameter WRITING_3		= 4;
	parameter WROTE			= 5;
	parameter WROTE_2		= 6;
	parameter WROTE_3		= 7;


	initial
		state <= WAIT;
	
	always @ (posedge clk)
		if(reset)
			begin
				newout <= 0;
				rd <= 1;			//we can't read data
				state <= WAIT;
			end
		else
			if(~hold)
				begin
					newout <= 0;
					case(state)
					WAIT:
						success <= 0;
						if(newin && ~TXE) begin
							wr <= 1;
							in_stored <= in;
							state <= WRITING;
						end
					WRITING:
						state <= WRITING_2;

					WRITING_2;
						state <= WRITING_3;

					WRITING_3;
						wr <= 0;
						state <= WROTE

					WROTE:
						state <= WROTE_2;

					WROTE_2:
						state <= WROTE_3;

					WROTE_3:
						success <= 1;
						state <= WAIT;							

					default:
						state <= WAIT;
				endcase		
			end
endmodule