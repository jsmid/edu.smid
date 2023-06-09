#!/usr/bin/env python
# coding: utf-8

# # Exploring Data Using Pandas

# In[223]:


import pandas as pd


# In[224]:


# In order to display all columns, set the Pandas option 'display.max_columns' to 'None'.
pd.set_option('display.max_columns', None)
# to load input CSV file into the data frame
df = pd.read_csv('data/coaster_db.csv')
df


# In[225]:


# to show number of rows and columns
df.shape


# In[226]:


# to show first five rows
df.head(5)


# In[227]:


# to show the name of each column
df.columns


# In[228]:


# to show the type of each column
df.dtypes


# In[229]:


# to clean up the data frame of columns we're not going to need
df = df[['coaster_name', 
        # 'Length', 'Speed', 
        'Location', 'Status', 
        # 'Opening date',
        # 'Type', 
        'Manufacturer', 
        # 'Height restriction', 'Model', 'Height',
        # 'Inversions', 'Lift/launch system', 'Cost', 'Trains', 'Park section',
        # 'Duration', 'Capacity', 'G-force', 'Designer', 'Max vertical angle',
        # 'Drop', 'Soft opening date', 'Fast Lane available', 'Replaced',
        # 'Track layout', 'Fastrack available', 'Soft opening date.1',
        # 'Closing date', 
        # 'Opened', 
        # 'Replaced by', 'Website',
        # 'Flash Pass Available', 'Must transfer from wheelchair', 'Theme',
        # 'Single rider line available', 'Restraint Style',
        # 'Flash Pass available', 'Acceleration', 'Restraints', 'Name',
       'year_introduced', 'latitude', 'longitude', 'Type_Main',
       'opening_date_clean', 
       # 'speed1', 'speed2', 'speed1_value', 'speed1_unit',
       'speed_mph', 
       # 'height_value', 'height_unit', 
       'height_ft',
       'Inversions_clean', 'Gforce_clean']].copy()
df.head(5)


# In[230]:


# to convert object to date/time
df['opening_date_clean'] = pd.to_datetime(df['opening_date_clean'])
df.dtypes


# In[231]:


# to rename columns to give them uniform look
df = df.rename(columns={'coaster_name': 'Coaster_Name', 
                        'year_introduced': 'Year_Introduced',
                        'latitude': 'Latitude', 
                        'longitude': 'Longitude',
                        'opening_date_clean': 'Opening_Date', 
                        'speed_mph': 'Speed_mph',
                        'height_ft': 'Height_ft', 
                        'Inversions_clean': 'Inversions', 
                        'Gforce_clean': 'Gforce'})
df.columns


# In[232]:


# to identify undefined values
df.isna().sum()    


# In[233]:


# to find duplicates
df.loc[df.duplicated()]  


# In[234]:


# to test duplicity on key columns
df.loc[df.duplicated(subset=['Coaster_Name'])]


# In[235]:


# The method 'duplicated' always only shows the second duplicate line.
# So let's investigate one particular duplicate.
df.query('Coaster_Name == "Crystal Beach Cyclone"')
# All values are identical except 'Year_Introduced'.


# In[236]:


# Remove all duplicates with a certain number of columns that are the same.
df.duplicated(subset=['Coaster_Name', 'Location', 'Opening_Date'])
# Columns 'Coaster_Name', 'Location', 'Opening_Date' now becomes a 'compound key' that uniquely identifies each row. 
# The columns can be freely chosen.


# In[237]:


# Let's locate the rows that are not duplicated. For that, we need to inverse the result, using '~'.
~df.duplicated(subset=['Coaster_Name', 'Location', 'Opening_Date'])


# In[238]:


df.loc[~df.duplicated(subset=['Coaster_Name', 'Location', 'Opening_Date'])]


# In[239]:


# Notice that since we were dropping rows, the index now contains gaps. 
# To get rid of the gaps, reset the index.
# By default the method adds a new column 'index'. In order to get rid of it, run the method with 'drop=True'
df = df.loc[~df.duplicated(subset=['Coaster_Name', 'Location', 'Opening_Date'])].reset_index(drop=True).copy()
# Once we're done, we make the result our new cleaned-up data frame.
df


# ## Univariate Analysis

# In[240]:


import matplotlib.pylab as plt
plt.style.use('ggplot')


# In[241]:


# To count how many unique values occur in the data set, ordered from most to least occuring.
df['Year_Introduced'].value_counts()


# In[242]:


# let's plot the top 10
# ax = df['Year_Introduced'].value_counts() \
# .head(10).plot(kind='bar', title='Top 10 Years Coasters Introduced')
# ax.set_xlabel('Year Introduced')
# ax.set_ylabel('Count')


# In[243]:


# to show the histogram
# ax = df['Speed_mph'].plot(kind='hist', bins=40, title='Coaster Speed (mph)')
# ax.set_xlabel('Speed (mph)')


# In[244]:


# to show normalized histogram, i.e. kernel density plot (to run this code, scipy module is required!)
# ax = df['Speed_mph'].plot(kind='kde', title='Coaster Speed (mph)')


# ## Feature Relationships

# In[245]:


# scatter plot, showing relationship between speed and height
# df.plot(kind='scatter', x='Speed_mph', y='Height_ft', 
#         title='Coaster Speed vs. Height')
# plt.show() # to get rid of the information about the plot object


# In[246]:


import seaborn as sns
# Seaborn scatter plot allows us to have different colored dots based 
# on the year that the rollercoster was introduced
# sns.scatterplot(x='Speed_mph', y='Height_ft', 
#                 hue='Year_Introduced', data=df)
# plt.show()
# Now we can clearly see that not only speed correlates to the height 
# but also that higher coasters are built year after year.


# In[247]:


top_manufacturers = df['Manufacturer'].value_counts().head(11).keys()
top_manufacturers


# In[248]:


# Coasters produced by remaining manufacturers.
df['Manufacturer'].value_counts()[10:].sum()


# In[255]:


from mplcursors import cursor

def f(speed, height):
    r = df.query('Speed_mph==@speed and Height_ft==@height')
    cn_vals = r['Coaster_Name'].values
    m_vals  = r['Manufacturer'].values
    return '{} (man. {})'.format(cn_vals[0] if len(cn_vals)>0 else 'N/A', 
                                 m_vals[0] if len(m_vals)>0 else 'N/A')

df['Top_Manufacturer'] = [x if x in top_manufacturers else 'Other' for x in df['Manufacturer']]
ax = sns.scatterplot(x='Speed_mph', y='Height_ft', palette='husl',
                hue='Top_Manufacturer', style='Type_Main', data=df)
sns.move_legend(ax, "upper left", bbox_to_anchor=(1, 1))
crs = cursor(ax, hover=True)
crs.connect("add", lambda sel: sel.annotation.set_text(f(sel.target[0], sel.target[1])))

# crs.connect("add", lambda sel: sel.annotation.set_text(sel.target))

plt.show()


# In[250]:


# ax = df['Manufacturer'].value_counts() \
# .head(10).plot(kind='bar', title='Top 10 Manufacturers')


# In[251]:


# What if we want to compare more features at once?
# sns.pairplot(data=df, 
#              vars=['Year_Introduced', 'Speed_mph', 'Height_ft', 
#                    'Inversions', 'Gforce'],
#              hue='Type_Main',
#              corner=True,
#              diag_kind="hist"
#             )
# plt.show()


# In[252]:


# Another useful characteristic is a correlation.
df_corr = df[['Year_Introduced', 'Speed_mph', 'Height_ft', 'Inversions', 'Gforce']].dropna().corr()
df_corr


# In[253]:


# sns.heatmap(df_corr, annot=True)
# plt.show


# ## Question 1: What are the locations with the fastests rollercosters?
# (minimum of 10)

# In[254]:


# import numpy as np
# ax = df.query('Location != "Other"') \
#     .groupby('Location')['Speed_mph'] \
#     .agg(['count', 'mean', np.max]) \
#     .query('count >= 10') \
#     .sort_values('mean')[['mean', 'amax']] \
#     .plot(kind='barh', figsize=(12, 5), title='Average Coaster Speed by Location')
# ax.set_xlabel('Average Coaster Speed')
# plt.show()


# In[ ]:




