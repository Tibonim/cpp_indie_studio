local utils = require('scriptLua.utilsIA')

id = Binder:getCurrentIa()

x = Binder.getPosX(id)
z = Binder.getPosZ(id)

nbr = Binder.getNbrOfEntities()
strength = Binder.getStrength(id)

range = utils.calc_distance(0, 0, Binder.getRangeX(id), Binder.getRangeY(id))

nearenemy, distance = utils.get_near_enemy(x, z, nbr)

Binder.setAttack(id, false)

if (utils.can_attack(range, distance)) then
      Binder.setVelocity(id, 0)
      Binder.setAttack(id, true)
else
	utils.move(Binder, nearenemy, x, z, 0.004)
end