local M = {}

local function        calc_distance(xa, ya, xb, yb)
   local ac = math.pow(yb - ya, 2)
   local ab = math.pow(xb - xa, 2)

  return math.sqrt(ac + ab)
end

local function	get_near_enemy(x, z, nbr)
   nearenemy = -1
   i = 0
   distance = 50000
   newdistance = 50000
   while (i < nbr) do
        enemy = Binder.getEntityFromCollection(i)
        ax = Binder.getPosX(enemy)
        az = Binder.getPosZ(enemy)
        newdistance = calc_distance(x, z, ax, az)
        if (newdistance < distance) then
           distance = newdistance
           nearenemy = enemy
        end
        i = i + 1
   end
   return nearenemy, distance
end

local function can_attack(range, distance)
      if (range > distance) then
      	 return true
      else
	 return false
      end
end

local function move(Binder, nearenemy, x, z, speed)
      if nearenemy == -1 then
	 Binder.setVelocity(id, 0)
      	 return
	 end
      dx = Binder.getPosX(nearenemy)
      dz = Binder.getPosZ(nearenemy)
      --if (math.abs(dx - x) > math.abs(dz - z)) then
      --	 Binder.setDirection(id, dx - x, 0, 0)
      --elseif (math.abs(dz - z) > math.abs(dx - x)) then
      --	     Binder.setDirection(id, 0, 0, dz - z)
      Binder.setDirection(id, dx - x, 0, dz - z)
      Binder.setVelocity(id, speed)
      --end
end

M.calc_distance = calc_distance
M.get_near_enemy = get_near_enemy
M.can_attack = can_attack
M.move = move

return M