void maze_scan(bool initial) {
  while (1) { //infinite loop
a:    reading();
    if (sum == 0) {
      if (flag != 's') {
        delay(wait);
        (flag == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'l') ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
        flag = 's'; cross = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }

      else {
        m3 = millis();
        while (sum == 0) {
          reading(); m2 = millis();
          if (m2 - m3 > u_turn_timer) {
            delay(wait); headlight(1);
            (side == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp);
            while (s[2] == 0 && s[3] == 0) reading();
            (side == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
            scan[counter] = 4; counter++;
            flag = 's'; cross = 0; break;
          }
        }
      }

    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 0) {
        delay(wait);
        (cross == 1) ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (sum > 0) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 1) ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
        flag = 's'; cross = 0;
      }

      else if (sensor == 0b001100) motor(10 * spl, 10 * spr);
      //right side portion
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) motor(10 * spl, 6 * spr);
      else if (sensor == 0b000010) motor(10 * spl, 3 * spr);
      else if (sensor == 0b000011) motor(10 * spl, 0 * spr);
      else if (sensor == 0b000001) motor(10 * spl, -3 * spr);
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) motor(6 * spl, 10 * spr);
      else if (sensor == 0b010000) motor(3 * spl, 10 * spr);
      else if (sensor == 0b110000) motor(0 * spl, 10 * spr);
      else if (sensor == 0b100000) motor(-3 * spl, 10 * spr);
    }

    else if (sum == 3 || sum == 4 || sum == 5) { //only for sharp turn logic
      if (s[0] == 0 && s[5] == 1 && s[2] + s[3] > 0) {
        flag = 'l';
        while (s[0] == 0 && s[5] == 1 && s[2] + s[3] > 0) reading();
        if (s[0] == 0) {
          delay(node_delay); reading();
          if (sum > 0) {
            if (side == 1) cross = 1;
            (side == 1) ? scan[counter] = 1 : scan[counter] = 2;
            counter ++; headlight(1);
          }
        }
      }
      else if (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) {
        flag = 'r';
        while (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) reading();
        if (s[5] == 0) {
          delay(node_delay); reading();
          if (sum > 0) {
            if (side == 2) cross = 2;
            (side == 2) ? scan[counter] = 3 : scan[counter] = 2;
            counter ++; headlight(1);
          }
        }
      }
      m1 = millis();
    }

    else if (sum == 6) {
      m3 = millis(); flag = 's'; cross = 0;
      while (s[0] == 1 || s[5] == 1) {
        reading(); m2 = millis();
        if (m2 - m3 > stop_timer) {
          motor(0, 0);
          scan[counter] = 5; algorithm();
          if (initial == 1) {
            motor(100, -100); delay(rotate);
            motor(-100, 100); delay(tbr); motor(0, 0);
            maze_solve(1);
          }
          return;
        }
      }
      if (m2 - m3 < stop_timer) {
        delay(node_delay); reading();
        if (sum == 0) (side == 1) ? flag = 'l' : flag = 'r';
        else (side == 1) ? cross = 1 : cross = 2;
        (side == 1) ? scan[counter] = 1 : scan[counter] = 3;
        counter ++; headlight(1);
      }
      m1 = millis();
    }
    m2 = millis();
    if (m2 - m1 > 200) {
      flag = 's'; headlight(0);
    }
  }
}
