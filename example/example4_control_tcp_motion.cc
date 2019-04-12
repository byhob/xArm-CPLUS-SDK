/* Copyright 2017 UFACTORY Inc. All Rights Reserved.
 *
 * Software License Agreement (BSD License)
 *
 * Author: Jimy Zhang <jimy92@163.com>
 ============================================================================*/
#include <unistd.h>

#include "xarm/connect.h"
#include "xarm/instruction/uxbus_cmd_config.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Please enter IP address\n");
    return 0;
  }
  char *server_ip = argv[1];
  UxbusCmd *arm_cmd = connect_tcp_control(server_ip);
  if (arm_cmd == NULL) return 0;

  int ret = arm_cmd->motion_en(8, 1);
  printf("motion_en, ret = %d\n", ret);

  ret = arm_cmd->set_mode(XARM_MODE::POSE);
  printf("set_state, ret = %d\n", ret);

  ret = arm_cmd->set_state(XARM_STATE::START);
  printf("set_state, ret = %d\n", ret);

  ret = arm_cmd->move_gohome(20.0 / 57.0, 1000, 0);
  printf("move_gohome, ret = %d\n", ret);

  ret = arm_cmd->sleep_instruction(0.1);
  printf("sleep_instruction, ret = %d\n", ret);

  float pose[5][6] = {
    {300,  0,   100, -3.14, 0.3, 0.5},
    {300,  100, 100, -3.14, 0.4, 0.1},
    {400,  100, 100, -3.14, 0.1, 0.2},
    {400, -100, 100, -3.14, 0.2, 0.2},
    {300,  0,   300, -3.14, 0.5, 0.3}
  };

  for (int i = 0; i < 5; i++) {
    ret = arm_cmd->move_lineb(pose[i], 50, 100, 0, 0);
    printf("move_lineb, ret = %d\n", ret);
  }

  arm_cmd->close();
}