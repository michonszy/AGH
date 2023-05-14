dane <- read.csv('dane_grA.csv')
#œrednia
sredniaZadluzenia <- mean(dane$Zadluzenie) 
sredniaInflacji <- mean(dane$Inflacja)

#mediana
medianaZadluzenie <- median(dane$Zadluzenie) 
head(dane)

summary(dane)

boxplot(dane$Zadluzenie, range=1, horizontal = TRUE, col = "cornflowerblue")
medianaInflacji <- median(dane$Inflacja) 

#dolny kwartyl
#górny kwartyl -> widoczne w summary
summary(dane$Zadluzenie)
summary(dane$Inflacja)
Q1_zadl <- quantile(dane$Zadluzenie,.25,na.rm=TRUE)
Q3_zadl <- quantile(dane$Zadluzenie,.75,na.rm=TRUE)

Q1_infl <- quantile(dane$Inflacja,.25,na.rm=TRUE)
Q3_infl <- quantile(dane$Inflacja,.75,na.rm=TRUE)

#moda
modaZadluzenie <- modeest::mfv(dane$Zadluzenie)
modaInflacji <- modeest::mfv(dane$Inflacja)

#wariancja
wariancjaZadluzenia <- var(dane$Zadluzenie)
wariancjaInflacji <- var(dane$Inflacja)

#kurtoza
library(moments)
kurtozaZadluzenia <- kurtosis(dane$Zadluzenie)
kurtozaInflacji <- kurtosis(dane$Inflacja)

#odchylenie standardowe
odchStandardZadluzenia <- sd(dane$Zadluzenie)
odchStandardInflacji <- sd(dane$Inflacja)


#histogram
hist(dane$Zadluzenie,main="Histogram zad³u¿enia",xlab="Zad³u¿enie",ylab="Czêstotliwoœæ")

#wykres rozrzutu
plot(dane$Zadluzenie,dane$Inflacja)
#³adniej opisany wykres rozrzutu
plot(dane$Zadluzenie,dane$Inflacja, xlab="Zad³u¿enie",
     ylab="Inflacja [%]",main="Wykres rozrzutu zad³u¿enia od inflacji")


#korelacja
cor(dane$Zadluzenie,dane$Inflacja)
cor.test(dane$Zadluzenie,dane$Inflacja)
#p-val<aplha => korelacja jest istotna statystycznie


#####MODEL REGRESJI
#Inflacja - zmienna zale¿na
#Zad³u¿enie - zmienna niezale¿na
#Zad³u¿eniem modelujemy inflacjê
model <-lm(dane$Inflacja~dane$Zadluzenie)
#podsumowanie + wspó³czynniki
#weryfikacja ca³ego modelu
summary(model)
a<-summary(model)

#wykres
plot(dane$Zadluzenie,dane$Inflacja,ylab="Inflacja",xlab="Zadluzenie",main="Wykres równania regresji")
#na³o¿enie linii na wykres
abline(model,col="red")
