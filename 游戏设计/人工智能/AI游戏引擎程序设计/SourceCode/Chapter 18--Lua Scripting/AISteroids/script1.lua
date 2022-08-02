--Lua script for simple asteroids state Logic


	function doAsteroid()
		if gvDistAsteroid < 200 then
			ChangeState(gsSTATEATTACK)
		else
			ChangeState(gsSTATEAPPROACH)
		end
	end

	function regular()
		if gvWillCollide then
			ChangeState(gsSTATEEVADE)
		elseif gvIsPowerup and gvShotPower < gvMaxShotPower then
			ChangeState(gsSTATEGETPOWERUP)
		elseif gvIsAsteroid then
			doAsteroid()
		else
			ChangeState(gsSTATEIDLE)
		end
	end


	function stupid()
		ChangeState(gsSTATEIDLE)
	end
		
	function try()
		if gvWillCollide then
			ChangeState(gsSTATEEVADE)
		else
			ChangeState(gsSTATEAPPROACH)
		end
	end

	regular()


