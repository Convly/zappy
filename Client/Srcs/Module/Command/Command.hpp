/*
** Command.hpp for PSU_2016_zappy in /Users/metge_q/rendu/PSU_2016_zappy/Client/Srcs/Module/Command
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Jun 26 14:08:05 2017 Quentin Metge
** Last update Sun Jul 02 11:49:18 2017 Quentin Metge
*/

#ifndef COMMAND_HPP_
# define COMMAND_HPP_

#include <iostream>
#include <mutex>
#include <algorithm>
#include <sstream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <queue>

namespace zpyclient{
  class Game;

  struct Command{
    void        setCmd(std::string const& str);

  public:
    static void execCmds(Game& game, Command& command);

  public:
    static void cmd_msz(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_bct(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_tna(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pnw(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_ppo(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_plv(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pin(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pex(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pbc(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pic(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pie(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pfk(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pdr(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pgt(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_pdi(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_enw(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_eht(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_ebo(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_edi(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_sgt(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_seg(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_smg(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_suc(Game& game, std::vector<std::string>& cmdArgs);
    static void cmd_sbp(Game& game, std::vector<std::string>& cmdArgs);

  public:
    static void createCell(Game& game, std::vector<std::string>& cmdArgs, size_t x, size_t y);

  private:
    std::string               _name;
    std::vector<std::string>  _args;
  };
}

#endif
