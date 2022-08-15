import time

from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.action_chains import ActionChains

time.sleep(1)

chrome_options = Options()
chrome_options.add_experimental_option("debuggerAddress", "127.0.0.1:9222")
driver = webdriver.Chrome( chrome_options=chrome_options)

driver.get("https://www.bing.com")


# driver.execute_script("console.log(\"hi\")")

base_url = "https://www.bing.com/search?q="
query = ""
for x in range(30):
   query += "a"
   url = base_url + query
   driver.get(url)


# clicking the sign in text
# driver.find_element(By.ID , "id_s").click()
# WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.ID, "id_s"))).click()
# element.click()
