dane <- read.csv('cisnienie.csv')
head(dane)

summary(dane)

dane <- read.csv('cisnienie.csv', stringsAsFactors = TRUE)

#histogram z podstawowego pakietu
hist(dane$Cisnienie.skurczowe)
hist(dane$Cisnienie.skurczowe, breaks=5)
hist(dane$Cisnienie.skurczowe,breaks=seq(140,240,10))

library(tidyverse)
ggplot(dane,aes(x=Cisnienie.skurczowe))+
  geom_histogram(bins = 10)

