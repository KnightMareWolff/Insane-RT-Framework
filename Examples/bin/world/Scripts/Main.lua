---------------------------------------------------------------------------------
--Insane Engine 3D - Script Principal
---------------------------------------------------------------------------------

--------------------------------------------------------------------
--Imprescindivel a utilizacao deste trecho para o inicio da execucao
--do Script.Basicamente ele permite que o sistema seja inicializado
--antes da logica do jogo e desta forma sincronizá-los
--------------------------------------------------------------------
while ICR_SystemOk()==false do
end

local cam    = CICRCamera:new();

function front()
   cam:Move(ICR_FRONT);
end

function back()
   cam:Move(ICR_BACK);
end

function left()
   cam:Move(ICR_LEFT);
end

function right()
   cam:Move(ICR_RIGHT);
end

function sair()
   ICR_ShutDown();
end

function spawn()
   ICR_ShutDown();
end

------------------------------------------------------
--Registra a execução das funções nas teclas
--Pressionadas.(W,S,A,D,ESC) na Pipeline de execução.
------------------------------------------------------
ICR_RegisterKbFunction(ICR_W_KEY  ,"front");
ICR_RegisterKbFunction(ICR_S_KEY  ,"back");
ICR_RegisterKbFunction(ICR_A_KEY  ,"left");
ICR_RegisterKbFunction(ICR_D_KEY  ,"right");
ICR_RegisterKbFunction(ICR_ESC_KEY,"sair");

--------------------------------------------------------------------
--Imprescindivel a utilizacao deste trecho para o inicio da execucao
--do Jogo.Basicamente ele permite que as inicializacoes para a Volta
--sejam realizadas antes do inicio do jogo e assim sincroniza-los
--------------------------------------------------------------------
while ICR_SystemRunning()==false do
end

------------------------------------------------
--Loop Principal do Jogo
------------------------------------------------
while ICR_SystemRunning() do
end
