----------------------------------------------------------------------------------
-- Company: Universidade de Aveiro
-- Engineer: Daniel Vala Correia
-- 
-- Create Date: 28.03.2021 18:16:40
-- Design Name: 
-- Module Name: pulse_generator_sel_1Hz_2Hz - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pulse_generator_sel_1Hz_2Hz is
    Port ( clk   : in STD_LOGIC;
           reset : in STD_LOGIC;
           sel   : in STD_LOGIC_VECTOR(3 downto 0);
           pulse : out STD_LOGIC);
end pulse_generator_sel_1Hz_2Hz;

architecture Behavioral of pulse_generator_sel_1Hz_2Hz is
    constant MAX : natural := 100_000_000;
    signal s_cnt : natural range 0 to MAX-1;
begin

    process(clk)
    begin
        if (rising_edge(clk)) then
            pulse <= '0';
            if (reset = '1') then
                s_cnt <= 0;
            else
                s_cnt <= s_cnt + 1;
                if (sel(0) = '0') then
                    if (s_cnt = MAX-1) then
                        s_cnt <= 0;
                        pulse <= '1';
                    end if;
                elsif (sel(0) = '1') then
                    if (s_cnt = ((MAX/2)-1)) then
                        s_cnt <= 0;
                        pulse <= '1';
                    end if;
                end if;
            end if;
        end if;
    end process;
    
end Behavioral;
