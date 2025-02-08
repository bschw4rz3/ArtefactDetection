import plotly.express as px
import pandas as pd
from IPython.display import display

dataframe = pd.read_csv('feature/feature_c_KNN_gray.csv', sep=';', header=None)
dataframe.columns = ["Anomaly", "skewness", "kurtosis", "entropy"]

display(dataframe)

fig = px.scatter_3d(dataframe, x=dataframe.columns[1], y=dataframe.columns[2], z=dataframe.columns[3], color=dataframe.columns[0])
fig.show()