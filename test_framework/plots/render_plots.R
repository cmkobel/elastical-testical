library(tidyverse)
library(ggpubr)
library(svglite)

setwd("~/bioinformatics/hmm/git2_hmmmlib/test_framework/plots")
#data <- read_csv("../time2.csv",)
#data <- read_csv("../short.csv")
#data <- read_csv("../medium.csv")
#data <- read_csv("../oct-31.csv")
#data <- read_csv("../oct-31-2.csv")

data = read_csv("../../hmmmlib/build/withblas.csv")

data_grouped = data %>% group_by(observations, algorithm, variant, type) %>% 
    summarise(mean = mean(time), sd = sd(time)) 




p_mean = data_grouped %>% ggplot(aes(observations, mean, color = variant, shape = type)) +
    geom_point() + 
    geom_line() + 
    geom_errorbar(aes(ymin=(mean-sd), ymax=(mean+sd) ), width = 10000, size = 0.1) +
    facet_wrap(.~algorithm, scales = "free") +
    labs(y = "mean time [s]", caption = "error bars: standard deviation")
p_mean

p_mean_normalized = data_grouped %>% ggplot(aes(observations, mean/observations, color = variant, shape = type)) +
    geom_point() + 
    geom_line() + 
    geom_errorbar(aes(ymin=(mean-sd)/observations, ymax=(mean+sd)/observations ), width = 10000, size = 0.1) +
    facet_wrap(.~algorithm, scales = "free") +
    labs(y = "normalized mean time [s]", caption = "error bars: standard deviation")
p_mean_normalized


ggsave("all.pdf", height = 5, width = 7, plot = p_mean)
ggsave("all_normalized.pdf", height = 5, width = 7, plot = p_mean_normalized)


















