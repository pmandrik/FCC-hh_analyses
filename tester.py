

import os

# import ahadd

class Channel():
  def __init__(self):
    self.name = ""
    self.chunks = []
    self.bad_chunks = []
    self.good_chunks = []

    self.files = []

    self.total_events = 0
    self.selected_events = 0

def get_folders(path):
  return [os.path.join(path, o) for o in os.listdir(path) if os.path.isdir(os.path.join(path,o))]

def check_file(file, checker):
  try:
    if checker in open( file ).read(): return True
  except : pass
  return None

def get_line(file, checker):
  try:
    f = open( file )
    for line in f:
      if checker in line: return line
    return None
  except : pass
  return None


DEBUG = True
DO_HADD = False
if __name__ == '__main__':
  from sys import argv
  
  path = argv[1]

  folders = get_folders( path )

  channels = []

  for folder in folders:
    # check if skippible
    channle_name, chunk_id = None, None
    try:
      channle_name = folder.split("_Chunk")[0].split("/")[1]
      chunk_id     = folder.split("_Chunk")[1]
    except:
      if DEBUG : print "skip ",folder
      continue

    # get channel
    # channel = channels.find(lambda x: x.name == channle_name)
    channel = next((x for x in channels if x.name == channle_name), None)
    if not channel : 
      channel = Channel()
      channel.name = channle_name
      channels += [ channel ]

    # check status
    channel.chunks += [ chunk_id ]
    subfolders = get_folders( folder )

    lsf_folder = next((x for x in subfolders if "LSF" in x), None)
    if not lsf_folder : 
      channel.bad_chunks += [ chunk_id ]
      if DEBUG : print folder, "- no LSF folder !"
      continue

    line_events          = get_line(lsf_folder + "/STDOUT", "heppy.FCChhAnalyses.analyzers.Reader.Reader_1")
    # line_selected_events = get_line(lsf_folder + "/STDOUT", "heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer.TreeProducer_1")
    line_selected_events = get_line(lsf_folder + "/STDOUT", "heppy.FCChhAnalyses.FCChh.FCNC_tqH.TreeProducer.TreeProducer_1")
    
    if not line_events or not line_selected_events:
      channel.bad_chunks += [ chunk_id ]
      if DEBUG : print folder, "- batch error !"
      continue

    # get number of events
    channel.total_events    += int( line_events.split()[0] )
    channel.selected_events += int( line_selected_events.split()[0] )

    # get output tree
    # file = os.path.abspath( folder + "/heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer.TreeProducer_1/tree.root")
    file = os.path.abspath( folder + "/heppy.FCChhAnalyses.FCChh.FCNC_tqH.TreeProducer.TreeProducer_1/tree.root")
    if not os.path.isfile( file ):
      channel.bad_chunks += [ chunk_id ]
      if DEBUG : print folder, "- no output file error !"
      continue

    channel.files += [file]
    channel.good_chunks += [ chunk_id ]

  for channel in channels:
    print channel.name, "[ events = ", channel.selected_events, "/", channel.total_events, "=",
    print float(channel.selected_events) / channel.total_events if channel.total_events else "0", "]",

    print "[ chunks = ", len(channel.good_chunks), "/", len(channel.chunks), "=",
    print float(len(channel.good_chunks)) / len(channel.chunks) if len(channel.chunks) else "0", "]"

    #if len(channel.files) and DO_HADD:
      #h = ahadd.hadd(channel.name + ".root", channel.files, None, force_overwrite = True)
      #h.run()





