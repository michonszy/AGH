dane <- read.csv('dane_grA.csv')
#�rednia
sredniaZadluzenia <- mean(dane$Zadluzenie) 
sredniaInflacji <- mean(dane$Inflacja)

#mediana
medianaZadluzenie <- median(dane$Zadluzenie) 
head(dane)

summary(dane)

boxplot(dane$Zadluzenie, range=1, horizontal = TRUE, col = "cornflowerblue")
medianaInflacji <- median(dane$Inflacja) 

#dolny kwartyl
#g�rny kwartyl -> widoczne w summary
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
hist(dane$Zadluzenie,main="Histogram zad�u�enia",xlab="Zad�u�enie",ylab="Cz�stotliwo��")

#wykres rozrzutu
plot(dane$Zadluzenie,dane$Inflacja)
#�adniej opisany wykres rozrzutu
plot(dane$Zadluzenie,dane$Inflacja, xlab="Zad�u�enie",
     ylab="Inflacja [%]",main="Wykres rozrzutu zad�u�enia od inflacji")


#korelacja
cor(dane$Zadluzenie,dane$Inflacja)
cor.test(dane$Zadluzenie,dane$Inflacja)
#p-val<aplha => korelacja jest istotna statystycznie


#####MODEL REGRESJI
#Inflacja - zmienna zale�na
#Zad�u�enie - zmienna niezale�na
#Zad�u�eniem modelujemy inflacj�
model <-lm(dane$Inflacja~dane$Zadluzenie)
#podsumowanie + wsp�czynniki
#weryfikacja ca�ego modelu
summary(model)
a<-summary(model)

#wykres
plot(dane$Zadluzenie,dane$Inflacja,ylab="Inflacja",xlab="Zadluzenie",main="Wykres r�wnania regresji")
#na�o�enie linii na wykres
abline(model,col="red")
