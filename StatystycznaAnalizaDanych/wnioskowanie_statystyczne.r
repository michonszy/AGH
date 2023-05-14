dochod <- c(360, 640, 490, 210, 280, 470, 580, 190, 320)
dom <- c(1.49, 3.10, 2.60, 0.92, 1.26, 2.42, 2.88, 0.81, 1.34)
#wspolczynnik korelacji
cor(dochod,dom)
#H0: kor-0, H1: kor != 0 alpha = 0,05
cor.test(dochod,dom)
#p-val<aplha => korelacja jest istotna statystycznie
#wykres rozrzutu
plot(dochod,dom)

#�adniej opisany wykres rozrzutu
plot(dochod, dom, xlab="Roczny
dochod rodziny [tys. zl.]",
     ylab="Wartosc domu [mln. zl]")

#przechodzimy dalej do budowania modelu
#model regresji
#badaj�c korelacje nie ma znaczenia kolejno�� w przypadku wykresu jednak buduj�c model regresji ma to ju� znaczenie
#w tym przypadku badamy warto�� dou w zale�no�ci od dochodu
#dom - zmienna zale�na
#doch�d - zmienna niezale�na
#dochodem modelujemy warto�� domu

model <-lm(dom~dochod)
#podsumowanie + wsp�czynniki
#weryfikacja ca�ego modelu, test f
summary(model)
a<-summary(model)

#wykres
plot(dochod,dom)
#na�o�enie linii na wykres
abline(model,col="red")

#ANALIZA RESZT
#1. Losowo�� odchyle�
#wykres reszt
plot(dochod, model$residuals)
abline(h=0,col="green")
#2.homoscedastyczno��
install.packages("lmtest")
library(lmtest)
#H0: wyst�puje stale rozproszenie reszt (homoscedastyczno�� wyst�puje)
#H1: wyst�puje heteroscedastyczno��
bptest(model)
#p-val>aplha => H0

#3. Reszty maj� rozk�ad normalny
#H0 - reszty maj� rozk�ad normalny
#H1 - reszty nie maj� rozk�adu normalnego
shapiro.test(model$residuals)
#p-val > alpha => nie mamy podstaw do odrzucenia H0

#4.nieobci��ono�� reszt - czy �rednia z reszt ~ 0
mean(model$residuals)

#wsp�czynnik determinacji
a$r.squared

nowe <- data.frame(dochod=400)
predict(model, nowe)
