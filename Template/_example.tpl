# 注释
# 按行依次执行

# 添加点 (名称/发音/纬度/经度)
fix,PINAB/Pin Ab/30.57917 106.3
# 离场程序 所有跑道 删除 PINA2Z PINA3Z
dep,*,-,PINA2Z PINA3Z
# 进场程序 03跑道 添加 (识别/名称/航点名称)
star,03,+,NIX1L/RW03.NIX1L/NIXAL PP403 PP515 PP511 PM508
star,04,+,NIX1L/RW03.NIX1L/NIXAL PP403 PP515 PP511 PM508
# 进近程序 所有跑道 仅保留 I03-Z I04-Z
app,*,@,I03-Z I04-Z