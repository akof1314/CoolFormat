use work.multiplier_types.all;
use work.bv_arithmetic.all;
use std.textio.all;
entity multiplier is
  port (clk: in bit;
        load: in bit;
        multiplicand: in word;
        multiply_by: in word;
        ready: out bit;
        product_low: inout word;
        product_high: inout word);
end multiplier;
architecture mixed of multiplier is
  component reg_1
    port (clk: in bit;
          load: in bit;
          d: in bit;
          q: out bit);
  end component;
  component shift_reg_word
    port (clk: in bit;
          load: in bit;
          shift: in bit;
          clr: in bit;
          d: in word;
          d_s: in bit;
          q: out word;
          q_s: out bit);
  end component;
  component reg_word
    port (clk: in bit;
          load: in bit;
          d: in word;
          q: out word);
  end component;
  component adder
    port (a: in word;
          b: in word;
          c_in: in bit;
          s: out word;
          c_out: out bit);
  end component;
  component and_word
    port (a: in bit;
          b: in word;
          z: out word);
  end component;
  signal b: word;
  signal b_or_0: word;
  signal partial_product: word;
  signal c_in: bit;
  signal c_out: bit;
  signal c_to_p: bit;
  signal p_to_a: bit;
  signal p_and_c_load: bit;
  signal shift: bit;
  signal tied_0: bit := '0';
  alias a_0: bit is product_low(0);
begin --  mixed
  a_reg: shift_reg_word
    port map (clk => clk,
              load => load,
              shift => shift,
              clr => tied_0,
              d => multiplicand,
              d_s => p_to_a,
              q => product_low,
              q_s => open );
  b_reg: reg_word
    port map (clk => clk,
              load => load,
              d => multiply_by,
              q => b);
  p_reg: shift_reg_word
    port map (clk => clk,
              load => p_and_c_load,
              shift => shift,
              clr => load,
              d => partial_product,
              d_s => c_in,
              q => product_high,
              q_s => p_to_a);
  carry_reg: reg_1
    port map (clk => clk,
              load => p_and_c_load,
              d => c_out,
              q => c_in);
  b_gate: and_word
    port map (a => a_0,
              b => b,
              z => b_or_0);
  the_adder: adder
    port map (a => product_high,
              b => b_or_0,
              c_in => c_in,
              s => partial_product,
              c_out => c_out);
  -----------------------------------------------------------------------------
  --  Process:   controller
  --  Purpose:  sequences register loading and shifting
  --  Inputs:   clk, load
  --  Outputs:  p_and_c_load, shift, ready
  -----------------------------------------------------------------------------
  controller:
  process is
    constant Tpd_clk_load: Time := 5 ns;
    constant Tpd_clk_shift: Time := 5 ns;
    constant Tpd_clk_ready: Time := 5 ns;
  begin --  PROCESS controller
    p_and_c_load <= '0' after Tpd_Clk_Load;
    shift <= '0' after Tpd_clk_shift;
    ready <= '1' after Tpd_clk_ready;
    wait on clk until clk = '1' and load = '1';
    ready <= '0' after Tpd_clk_ready;
    for cycle in 1 to word_size
    loop
      p_and_c_load <= '1' after Tpd_clk_load;
      wait until clk = '1';
      p_and_c_load <= '0' after Tpd_clk_load;
      shift <= '1' after Tpd_clk_shift;
      wait until clk = '1';
      shift <= '0' after Tpd_clk_shift;
    end loop; --  cycle
    ready <= '1' after Tpd_clk_ready;
  end process controller;
end mixed;