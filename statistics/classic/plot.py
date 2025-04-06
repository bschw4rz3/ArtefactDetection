import plotly.express as px
import pandas as pd
from IPython.display import display

dataframe = pd.read_csv('feature/feature_c_KNN_Bior.csv', sep=';', header=None)
dataframe.columns = ["Anomaly", "minimal Amplitude", "maximal Amplitude", "kurtosis Amplitude", "datatype"]
#del dataframe['Kurtosis']
del dataframe['datatype']

display(dataframe)

fig = px.scatter_3d(dataframe, x=dataframe.columns[1], y=dataframe.columns[2], z=dataframe.columns[3], color=dataframe.columns[0], 
    color_continuous_scale=["red", "green"]
)
fig.show()