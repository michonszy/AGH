dane <- read.csv('placa.csv')
head(dane)
summary(dane)
dane <- read.csv('placa.csv', stringsAsFactors = TRUE)
#histogram
library(tidyverse)
#hist(dane$Wiek)
ggplot(dane,aes(x=Wiek))+
  geom_histogram(breaks=seq(0,200,10), color="black",fill="red",alpha=0.5)+
  labs(      #tu bêd¹ podpisy i opisy
    x = "wiek",
    y = "licznosc",
    title="Histogram wieku")

ggplot(dane,aes(x=Staz.pracy))+
  geom_histogram(breaks=seq(0,50,5), color="black",fill="red",alpha=0.5)+
  labs(      #tu bêd¹ podpisy i opisy
    x = "Sta¿ pracy",
    y = "licznosc",
    title="Histogram sta¿u pracy")


#wasy staz pracy
ggplot(dane,aes(x=Staz.pracy))+
  geom_boxplot(fill="cornflowerblue", outlier.colour = "darkred") +
  coord_flip()


ggplot(dane,aes(x=Placa.brutto))+
  geom_histogram(breaks=seq(0,7000,500), color="black",fill="red",alpha=0.5)+
  labs(      #tu bêd¹ podpisy i opisy
    x = "Placa brutto",
    y = "licznosc",
    title="Histogram p³acy brutto")

ggplot(dane,aes(x=Placa.brutto))+
  geom_boxplot(fill="cornflowerblue", outlier.colour = "darkred",outlier.shape =4, coef=1.5) +
  coord_flip()


#wykres ramka-w¹sy

#wykres s³upkowy

