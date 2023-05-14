dochod <- c(360, 640, 490, 210, 280, 470, 580, 190, 320)
dom <- c(1.49, 3.10, 2.60, 0.92, 1.26, 2.42, 2.88, 0.81, 1.34)
#wspolczynnik korelacji
cor(dochod,dom)
#H0: kor-0, H1: kor != 0 alpha = 0,05
cor.test(dochod,dom)
#p-val<aplha => korelacja jest istotna statystycznie
#wykres rozrzutu
plot(dochod,dom)

#³adniej opisany wykres rozrzutu
plot(dochod, dom, xlab="Roczny
dochod rodziny [tys. zl.]",
     ylab="Wartosc domu [mln. zl]")

#przechodzimy dalej do budowania modelu
#model regresji
#badaj¹c korelacje nie ma znaczenia kolejnoœæ w przypadku wykresu jednak buduj¹c model regresji ma to ju¿ znaczenie
#w tym przypadku badamy wartoœæ dou w zale¿noœci od dochodu
#dom - zmienna zale¿na
#dochód - zmienna niezale¿na
#dochodem modelujemy wartoœæ domu

model <-lm(dom~dochod)
#podsumowanie + wspó³czynniki
#weryfikacja ca³ego modelu, test f
summary(model)
a<-summary(model)

#wykres
plot(dochod,dom)
#na³o¿enie linii na wykres
abline(model,col="red")

#ANALIZA RESZT
#1. Losowoœæ odchyleñ
#wykres reszt
plot(dochod, model$residuals)
abline(h=0,col="green")
#2.homoscedastycznoœæ
install.packages("lmtest")
library(lmtest)
#H0: wystêpuje stale rozproszenie reszt (homoscedastycznoœæ wystêpuje)
#H1: wystêpuje heteroscedastycznoœæ
bptest(model)
#p-val>aplha => H0

#3. Reszty maj¹ rozk³ad normalny
#H0 - reszty maj¹ rozk³ad normalny
#H1 - reszty nie maj¹ rozk³adu normalnego
shapiro.test(model$residuals)
#p-val > alpha => nie mamy podstaw do odrzucenia H0

#4.nieobci¹¿onoœæ reszt - czy œrednia z reszt ~ 0
mean(model$residuals)

#wspó³czynnik determinacji
a$r.squared

nowe <- data.frame(dochod=400)
predict(model, nowe)
