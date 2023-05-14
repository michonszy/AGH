
gleba <- c(16,2, 15,4, 13,8, 18, 15,1, 17,3, 16,8, 15, 15,9, 16,5)
x_sr <- mean(gleba)
s <- sd(gleba)
t=qt(0.99,(10-1))
a<-(x_sr-s/sqrt(10-1)*t)
b<-(x_sr+s/sqrt(10-1)*t)

